/******************************************************************************
This is to certify that this project is my own work, based on my personal
efforts in studying and applying the concepts learned. I have constructed
the functions and their respective algorithms and corresponding code by
myself. The program was run, tested, and debugged by my own efforts. I
further certify that I have not copied in part or whole or otherwise
plagiarized the work of other students and/or persons.
Isaac Nathan Roman - 12208397 - S19B
******************************************************************************/
/*
    Description: A turn-based tiled shooter
    Programmed by: Isaac Nathan Roman, S19B
    Last modified: December 4, 2022 [9:02 PM]
    Version: 1.0
    Acknowledgements: Sir Lu for the Prompt

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define DEBUG_MODE // comment to turn off debug mode

void initializeVariables(int *nPoints, int *nStatus, int *nPowerPosition, int *nRounds, int *nPowerClaimed,
                        int *nMultiplier, int *nPlayerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2,
                        int *nEnemyPosition_3, int *nEnemyCycle_1, int *nEnemyCycle_2, int *nEnemyCycle_3);
void printField(int nPlayerPosition, int nEnemyPosition_1, int nEnemyPosition_2, int nEnemyPosition_3, int nPowerPosition);
void inputAction(int *nPlayerAction, int *nPlayerPosition);
void playerShoot(int *nPlayerShoot, int *nPlayerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2, int *nEnemyPosition_3, 
                        int *nEnemyCycle_1, int *nEnemyCycle_2, int *nEnemyCycle_3, int *nEnemyDeath, int *nPowerClaimed,
                        int *nPowerPosition, int *nRoundsLeft, int *nPoints, int *nMultiplier);
void updateEnemyPosition(int *nEnemy, int *nEnemyCycle);
void updatePowerUp(int *nRounds, int *nPowerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2, 
                        int *nEnemyPosition_3, int *nPowerClaimed, int *nMultiplier, int *nRoundsLeft);

int main(void){

    srand(time(NULL));

    // Player Variables
    int nPlayerPosition, nPlayerAction, nPlayerShoot;
    // Enemy Variables
    int nEnemyPosition_1, nEnemyCycle_1, nEnemyPosition_2, nEnemyCycle_2, nEnemyPosition_3, nEnemyCycle_3;
    // Game Variables
    int nPoints, nStatus, nEnemyDeath, nPowerPosition, nPowerClaimed, nRounds, nRoundsLeft, nMultiplier;

    initializeVariables(&nPoints, &nStatus, &nPowerPosition, &nRounds, &nPowerClaimed, &nMultiplier, &nPlayerPosition,
                        &nEnemyPosition_1, &nEnemyPosition_2, &nEnemyPosition_3, &nEnemyCycle_1, &nEnemyCycle_2, &nEnemyCycle_3);

    do{ // do-while ends when nStatus changes to 1 (victory) or 2 (defeated)
        #ifdef DEBUG_MODE
            printf("\nRound #%d, PowerUp: %d, nPowerClaimed: %d\n", nRounds, nPowerPosition, nPowerClaimed);
            printf("\n#1 Position: %d, #2 Position: %d, #3 Position: %d\n\n", nEnemyPosition_1, nEnemyPosition_2, nEnemyPosition_3);
        #endif

        // checks game status
        if(nPoints >= 100)
            nStatus = 1;
        if((nEnemyPosition_1 > 20) || (nEnemyPosition_2 > 20) || (nEnemyPosition_3 > 20))
            nStatus = 2;

        printField(nPlayerPosition, nEnemyPosition_1, nEnemyPosition_2, nEnemyPosition_3, nPowerPosition);

        if(nStatus == 0){ // prevents player movement/action when game is over
            
            // print score and action list
            printf("Score: %.3d", nPoints);
            if(nPowerClaimed > 0) // adds multiplier counter if power is claimed
                printf(" | 2x Multiplier [Rounds Left: %d]", nRoundsLeft);
            printf("\nActions:\n 1 - Move left\n 2 - Move right\n 3 - Fire laser\n");

            inputAction(&nPlayerAction, &nPlayerPosition);
            if(nPlayerAction == 3)
                playerShoot(&nPlayerShoot, &nPlayerPosition, &nEnemyPosition_1, &nEnemyPosition_2, &nEnemyPosition_3, &nEnemyCycle_1, 
                            &nEnemyCycle_2, &nEnemyCycle_3, &nEnemyDeath, &nPowerClaimed, &nPowerPosition, &nRoundsLeft, &nPoints, &nMultiplier);      
        }

        updateEnemyPosition(&nEnemyPosition_1, &nEnemyCycle_1);
        updateEnemyPosition(&nEnemyPosition_2, &nEnemyCycle_2);
        updateEnemyPosition(&nEnemyPosition_3, &nEnemyCycle_3);

        #ifdef DEBUG_MODE
            printf("\n#1 Cycle: %d, #2 Cycle: %d, #3 Cycle: %d\n", nEnemyCycle_1, nEnemyCycle_2, nEnemyCycle_3);
        #endif
        
        updatePowerUp(&nRounds, &nPowerPosition, &nEnemyPosition_1, &nEnemyPosition_2, &nEnemyPosition_3, &nPowerClaimed, &nMultiplier, &nRoundsLeft);

        nRounds++; 

    } while(nStatus == 0);

    // prints status (victory/defeated)
    if(nStatus == 1){
        printf("VICTORY!\n");
        printf("Final Score: %.3d\n", nPoints);
    }
    else if(nStatus == 2){
        printf("DEFEATED!\n");
        printf("Final Score: %.3d\n", nPoints);
    }

    return 0;
}   

/* 
DESCRIPTION:
    The 'intializeVariables' function initializes the necessary pre-game variables

PRECONDITION:
    All variables are integer-type.

PARAMETERS:
    @param *nPoints - Player's points
    @param *nStatus - Game status (win/lose/continue)
    @param *nPowerPosition - Represents powerup's position
    @param *nRounds - Represents game rounds
    @param *nPowerClaimed - Tracks if powerup is claimed
    @param *nMultiplier - Point multiplier
    @param *nPlayerPosition - Represents player's position
    @param *nEnemyPosition_1 - Represents enemy_1's position
    @param *nEnemyPosition_2 - Represents enemy_2's position
    @param *nEnemyPosition_3 - Represents enemy_3's position 
    @param *nEnemyCycle_1 - Represents enemy_1's algorithm cycle 
    @param *nEnemyCycle_2 - Represents enemy_2's algorithm cycle 
    @param *nEnemyCycle_3 - Represents enemy_3's algorithm cycle 

RETURN:
    This function does not return anything; void.
*/

void initializeVariables(int *nPoints, int *nStatus, int *nPowerPosition, int *nRounds, int *nPowerClaimed,
                        int *nMultiplier, int *nPlayerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2,
                        int *nEnemyPosition_3, int *nEnemyCycle_1, int *nEnemyCycle_2, int *nEnemyCycle_3){

    // Initial Settings
    *nPoints = 0; 
    *nStatus = 0; // 0 represents game continuing
    *nPowerPosition = 0; // represents powerup starting position
    *nRounds = 1; // start of round
    *nPowerClaimed = 0;
    *nMultiplier = 1; // intial score multiplier (pre-powerup)

    // Initial Positions (of Player & Enemies)
    *nPlayerPosition = 1; 
    *nEnemyPosition_1 = rand() % 4 + 1; // enemy spawnpoints are randomized
    *nEnemyPosition_2 = rand() % 4 + 1;
    *nEnemyPosition_3 = rand() % 4 + 1;

    // Initial Enemy Cycles
    *nEnemyCycle_1 = 1;
    *nEnemyCycle_2 = 1;
    *nEnemyCycle_3 = 1;
}

/* 
DESCRIPTION:
    The 'printField' function produces a grid divided into two portions;
    the enemy field and the player field.
    
PRECONDITION:
    Enemy and power up variables are non-negative values. The player variable
    must be between 1 or 4 inclusive.

PARAMETERS:
    @param nPlayerPosition - Represents player's position
    @param nEnemyPosition_1 - Represents enemy_1's position 
    @param nEnemyPosition_2 - Represents enemy_2's position 
    @param nEnemyPosition_3 - Represents enemy_3's position 
    @param nPowerPosition - Represents PowerUp's position

RETURN:
    This function does not return anything; void.
*/

void printField(int nPlayerPosition, int nEnemyPosition_1, int nEnemyPosition_2, int nEnemyPosition_3, int nPowerPosition){

    // prints enemy field
    printf("%c%c%c%c%c%c%c%c%c\n", 218, 196, 194, 196, 194, 196, 194, 196, 191);
    for(int i = 1; i <= 5; i++){
        for(int j = 1; j <= 9; j++){
            if(j%2 == 0){
                 // represents grid logic & checks if enemy is in grid; if so, print enemy
                if((4*(i-1) + (j/2)) == nEnemyPosition_1 || (4*(i-1) + (j/2)) == nEnemyPosition_2 || (4*(i-1) + (j/2)) == nEnemyPosition_3)
                    printf("X");
                else if((4*(i-1) + (j/2)) == nPowerPosition) // checks if powerup is in grid; if so, print powerup
                    printf("+");
                else
                    printf(" ");
            }
            else
                printf("%c", 179); // border
        }
        printf("\n");
    }
    printf("%c%c%c%c%c%c%c%c%c\n", 195, 196, 197, 196, 197, 196, 197, 196, 180);

    // prints player field
    for(int j = 1; j <= 9; j++){
        if(j%2 == 0)
            if(nPlayerPosition == j/2)
                printf("P");
            else
                printf(" ");
        else
            printf("%c", 179);      
    }
    printf("\n%c%c%c%c%c%c%c%c%c\n", 192, 196, 193, 196, 193, 196, 193, 196, 217);
}

/* 
DESCRIPTION:
    The 'inputAction' function prompts the user for input. If the input is movement-based,
    the player movement is adjust accordingly.
    
PRECONDITION:
    *nPlayerPosition's value/position must be a value in between 1 and 4 inclusive. *nPlayerAction is
    unassigned pre-function or contains the previous nPlayerAction value (after the first round).

PARAMETERS:
    @param *nPlayerAction - Represents the action of the player. (Unassigned at the start of the game)
    @param *nPlayerPosition - Represents player's position.

RETURN:
    This function does not return anything as the parameters passed are changed through
    pointer; void.
*/

void inputAction(int *nPlayerAction, int *nPlayerPosition){
    do{ // Only accepts valid input
        printf("Input action: ");
        scanf("%d", &*nPlayerAction);
        if(*nPlayerAction < 1 || *nPlayerAction > 3)
            printf("Invalid Input\n");

    // if player movement goes out of bounds, adjust position
    if(((*nPlayerAction==1 && *nPlayerPosition==1) || (*nPlayerAction==2 && *nPlayerPosition==4)))
        printf("Out of Bounds\n");

    } while((*nPlayerAction < 1 || *nPlayerAction > 3) || ((*nPlayerAction==1 && *nPlayerPosition==1) || (*nPlayerAction==2 && *nPlayerPosition==4)));

    // moves player if action is 1 or 2
    if(*nPlayerAction == 1)
        *nPlayerPosition -= 1;
    else if(*nPlayerAction == 2)
        *nPlayerPosition += 1;
}

/* 
DESCRIPTION:
    The 'playerShoot' function is activated if nAction is 3. This function
    calculates the proper response and updates the appropriate variables 
    if the player shoots an enemy or power-up.
    
PRECONDITION:
    All parameters are non-negative and nAction is 3.

PARAMETERS:
    @param *nPoints - Player's points
    @param *nPowerPosition - Represents powerup's position
    @param *nPowerClaimed - Tracks if powerup is claimed
    @param *nMultiplier - Point multiplier
    @param *nPlayerShoot - Represents where the player is shooting
    @param *nPlayerPosition - Represents player's position
    @param *nPlayerAction - Represents player's action
    @param *nEnemyPosition_1 - Represents enemy_1's position
    @param *nEnemyPosition_2 - Represents enemy_2's position
    @param *nEnemyPosition_3 - Represents enemy_3's position 
    @param *nEnemyCycle_1 - Represents enemy_1's algorithm cycle 
    @param *nEnemyCycle_2 - Represents enemy_2's algorithm cycle 
    @param *nEnemyCycle_3 - Represents enemy_3's algorithm cycle 
    @param *nEnemyDeath - Increments when an enemy dies
    @param *nRoundsLeft - Rounds left of powerUp activity
    
RETURN:
    This function does not return anything as the parameters passed are changed through
    pointer; void.
*/

void playerShoot(int *nPlayerShoot, int *nPlayerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2, int *nEnemyPosition_3, 
                        int *nEnemyCycle_1, int *nEnemyCycle_2, int *nEnemyCycle_3, int *nEnemyDeath, int *nPowerClaimed,
                        int *nPowerPosition, int *nRoundsLeft, int *nPoints, int *nMultiplier){

    // initializes which column to shoot
    *nPlayerShoot = 20 - (4 - *nPlayerPosition);
    *nEnemyDeath = 0; // when nEnemyDeath = 1, loop stops checking previous rows and only kills 1 enemy
    do{// goes to each block in column, checks for enemy/powerup and if there is, kill enemy/gain powerup
        if(*nPlayerShoot == *nEnemyPosition_1 || *nPlayerShoot == *nEnemyPosition_2 || *nPlayerShoot == *nEnemyPosition_3 || *nPlayerShoot == *nPowerPosition){
            // each if statement checks if nPlayerShoot hits enemy/powerup
            if(*nPlayerShoot == *nEnemyPosition_1 && *nEnemyDeath == 0){
                *nPoints += 10 * *nMultiplier;  
                *nEnemyPosition_1 = rand() % 4 + 1; // if enemy dies, they are assigned the random spawnpoint
                *nEnemyCycle_1 = 1;
                *nEnemyDeath += 1;
                #ifdef DEBUG_MODE
                    printf("\nEnemy #1 Died; Spawns back in %d\n", *nEnemyPosition_1);
                #endif
            }
            if(*nPlayerShoot == *nEnemyPosition_2 && *nEnemyDeath == 0){
                *nPoints += 10 * *nMultiplier;  
                *nEnemyPosition_2 = rand() % 4 + 1;
                *nEnemyCycle_2 = 1;
                *nEnemyDeath += 1;    
                #ifdef DEBUG_MODE
                    printf("\nEnemy #2 Died; Spawns back in %d\n", *nEnemyPosition_2);
                #endif             
            }
            if(*nPlayerShoot == *nEnemyPosition_3 && *nEnemyDeath == 0){
                *nPoints += 10 * *nMultiplier;  
                *nEnemyPosition_3 = rand() % 4 + 1;
                *nEnemyCycle_3 = 1;     
                *nEnemyDeath += 1;     
                #ifdef DEBUG_MODE
                    printf("\nEnemy #3 Died; Spawns back in %d\n", *nEnemyPosition_3);
                #endif          
            }
            if(*nPlayerShoot == *nPowerPosition && *nEnemyDeath == 0){
                *nPowerClaimed += 1;
                *nPowerPosition = 0;
                *nRoundsLeft = 4;
                #ifdef DEBUG_MODE
                    printf("PowerUp Claimed\n");
                #endif
            }
        }
        *nPlayerShoot -= 4; // Check previous row in same column  
    } while(*nPlayerShoot > 0 && *nEnemyDeath == 0); // end while once laser hits end of row OR an enemy dies

}

/* 
DESCRIPTION:
    The 'updateEnemyPosition' function updates the enemy position depending on their cycle
    
PRECONDITION:
    *nEnemy and *nEnemyCycle are non-negative values

PARAMETERS:
    @param *nEnemy - Represents the corresponding enemy's position 
    @param *nEnemyCycle - Represents the corresponding enemy's algorithm cycle

RETURN:
    This function does not return anything as the parameters passed are changed through
    pointer; void.
*/

void updateEnemyPosition(int *nEnemy, int *nEnemyCycle){

   // Restarts enemy algorithm back to 1 
    if(*nEnemyCycle > 4){
        *nEnemyCycle = 1;
   }

    if(*nEnemyCycle == 1){
        // If enemy is in rightmost border, move down instead of moving right
        if(*nEnemy == 4 || *nEnemy == 8 || *nEnemy == 12 || *nEnemy == 16 || *nEnemy == 20 )
            *nEnemy += 4;
        else
            *nEnemy += 1;
    }
    else if(*nEnemyCycle == 2 || *nEnemyCycle == 4)
        *nEnemy += 4;
    else if(*nEnemyCycle == 3){
        // If enemy is in leftmost border, move down instead of moving left
        if(*nEnemy == 1 || *nEnemy == 5 || *nEnemy == 9 || *nEnemy == 13 || *nEnemy == 17 )
            *nEnemy += 4;
        else
            *nEnemy -= 1;
    }
    *nEnemyCycle += 1; // LEARNING: *nEnemyCycle++ doesn't properly function? possibly because it's incrementing its address.
}

/* 
DESCRIPTION:
    The 'updatePowerUp' function updates the position of the power up. It also
    covers cases when the player gains the power up or if the enemy collides with it.
    
PRECONDITION:
    All parameters are non-negative

PARAMETERS:
        @param *nPowerPosition - Represents powerup's position
        @param *nPowerClaimed - Tracks if powerup is claimed
        @param *nMultiplier - Point multiplier
        @param *nEnemyPosition_1 - Represents enemy_1's position
        @param *nEnemyPosition_2 - Represents enemy_2's position
        @param *nEnemyPosition_3 - Represents enemy_3's position 
        @param *nRoundsLeft - Rounds left of powerUp activity
        @param *nRounds - Represents which round the game is in

RETURN:
    This function does not return anything as the parameters passed are changed through
    pointer; void.
*/

void updatePowerUp(int *nRounds, int *nPowerPosition, int *nEnemyPosition_1, int *nEnemyPosition_2, 
                        int *nEnemyPosition_3, int *nPowerClaimed, int *nMultiplier, int *nRoundsLeft){
        
    // Power up spawns after every 5 rounds
    if(*nRounds%5 == 0){
        do{
            *nPowerPosition = rand() % 20 + 1;
        } while(*nPowerPosition == *nEnemyPosition_1 || *nPowerPosition == *nEnemyPosition_2 || *nPowerPosition == *nEnemyPosition_3); // end while if powerup doesn't spawn in enemy's place
    }

    // power up gets removed if enemy collides with it
    if(*nPowerPosition == *nEnemyPosition_1 || *nPowerPosition == *nEnemyPosition_2 || *nPowerPosition == *nEnemyPosition_3)
        *nPowerPosition = 0;

    // if power up is claimed; once claimed it decrements by 1
    if(*nPowerClaimed >= 1){
        *nMultiplier = 2;
        *nRoundsLeft -= 1;
    }
    // turns multiplier off once 3 rounds is over
    if (*nRoundsLeft == 0){
        *nPowerClaimed = 0;
        *nMultiplier = 1;
    }
}
