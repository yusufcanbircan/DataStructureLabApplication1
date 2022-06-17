// @yusufcanbircan

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* functionFindMin(int* array, int row, int cols, char source, char destination){

    int destinations[50][15];
    int destinationsRoad[50][11];
    int destinationsSum[50];
    int roads[100][3];
    int roadCounter = 0, counter = 0;

    for(int i = 1; i < 11; i++){
        for (int j = 1; j < 11; j++){
            if( *((array + 11 * i) + j) != 0 && *((array + 11 * i) + j) != -1){
                roads[counter][0] = *((array + 11 * i) + 0);
                roads[counter][1] = *((array + 11 * 0) + j);
                roads[counter][2] = *((array + 11 * i) + j);
                counter++;
            }
        }
    }

    for(int i = 0; i<50; i++){
        destinationsRoad[i][0] = 0;
        destinationsSum[i] = 0;
    }

    
    int checkSame = 0, tryTime = 0;

    for(int i = 0; i < counter; i++){
        if(roads[i][0] == (int)source){
            destinations[roadCounter][0] = source;
            destinationsRoad[roadCounter][1] = source;
            destinationsRoad[roadCounter][0]++;
            roadCounter++;
            //----
            tryTime = 0;
            for(int j = 0; j < counter; j++){
                if(roads[i][0] == roads[j][0]){
                    tryTime++;
                }
            }

            if(tryTime != 0){
                for(int j = 1; j < tryTime; j++){
                    for(int m = 0; m < 15; m++){
                        destinations[roadCounter][m] = destinations[roadCounter-1][m];
                    }
                    for(int m = 0; m < 15; m++){
                        destinationsRoad[roadCounter][m] = destinationsRoad[roadCounter-1][m];
                    }
                    roadCounter++;
                }
            }
            break;
        }
    }

    int loopTime = 0;
    while (1)
    {
        for(int i = 0; i < counter; i++){
            for(int j = 0; j < roadCounter; j++){
                tryTime = 0;
                checkSame = 0;

                if(destinations[j][destinationsRoad[j][0]-1] != (int)destination && destinations[j][destinationsRoad[j][0]-1] == roads[i][0]){

                    for(int k = 0; k < destinationsRoad[j][0]+1; k++){
                        if(roads[i][1] == destinationsRoad[j][k]){
                            checkSame++;
                        }
                    }
                    if(checkSame == 0){
                        destinations[j][destinationsRoad[j][0]] = roads[i][1];
                        destinationsSum[j] += roads[i][2];
                        destinationsRoad[j][destinationsRoad[j][0]+1] = roads[i][1];
                        destinationsRoad[j][0]++;
                    }
                    for(int m = 0; m < counter; m++){
                        if(roads[m][0] == destinations[j][destinationsRoad[j][0]-1]){
                            for(int n = 1; n < destinationsRoad[j][0]+1; n++){
                                if(roads[m][1] == destinationsRoad[j][n]){
                                    tryTime++;
                                }
                            }
                            if(tryTime == 0){
                                destinationsSum[roadCounter] = destinationsSum[j];
                                for(int n = 0; n < 15; n++){
                                    destinations[roadCounter][n] = destinations[j][n];
                                }
                                for(int n = 0; n < 11; n++){
                                    destinationsRoad[roadCounter][n] = destinationsRoad[j][n];
                                }
                                destinations[roadCounter][destinationsRoad[roadCounter][0]] = roads[m][1];
                                destinationsSum[roadCounter] += roads[m][2];
                                destinationsRoad[roadCounter][destinationsRoad[roadCounter][0]+1] = roads[m][1];
                                destinationsRoad[roadCounter][0]++;
                                roadCounter++;
                            }
                            tryTime = 0;
                        }
                    }
                    break;
                }
            }
        }
        break;
    }

    int min = 5000;
    int minIndex;
    int endCounter = 0;

    for(int i = 0; i < roadCounter; i++){
        if(destinations[i][0] == (int)source && destinations[i][destinationsRoad[i][0]-1] == (int)destination){
            endCounter++;
            if(destinationsSum[i] <= min){
                min = destinationsSum[i];
                minIndex = i;        
            }
        }
    }
    int endArray[50];
    int* endArrayptr = &endArray[0];

    if(endCounter != 0){
        endArray[0] = destinationsRoad[minIndex][0];
        endArray[1] = destinationsSum[minIndex];
        for(int i = 2; i < endArray[0]+2; i++){
            endArray[i] = destinations[minIndex][i-2];
        }
        
        return endArrayptr;
    }
    else{
        endArray[0] = 9898;
        return endArrayptr;
    }
}

int main(){

    int array[11][11];
    int input;
    char source, destination;
    int *retIndex;
    
    char str[10] = "ABCDEFGHIJ";

    // Adding letters to array.
    array[0][0] = 0;
    for(int i = 1; i < 11; i++){
        array[0][i] = str[i-1];
        array[i][0] = str[i-1];
    }

    //Taking roads.
    for(int i = 1; i < 11; i++){
        for(int j = 1; j < 11; j++){
            scanf("%d", &input);
            array[i][j] = input;
        }
    }

    scanf(" %c %c", &source, &destination);

    retIndex = functionFindMin(&array[0][0], 11, 11, source, destination);

    if(*retIndex == 9898){
        printf("You cannot travel between two cities");
    }
    else{
        for(int i = 2; i < *(retIndex)+2; i++){
            printf("%c", *(retIndex+i));
            if(i != *(retIndex)+1){
                printf("-");
            }
        }
        printf(" %d", *(retIndex+1));
    }
    printf("\n");

    return 0;
}
