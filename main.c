//
//  main.c
//  12_SharkGame
//
//  Created by ok sojoung on 2023/11/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameboard.h"

#define MAX_DIE     6

void opening(void)
{
    printf("=====================================================\n");
    printf("*****************************************************\n");
    printf("                        BINGO GAME                   \n");
    printf("*****************************************************\n");
    printf("=====================================================\n");
}


int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

// ----------------------------------------------------
int main(void) 
{
    int pos = 0;
    // rand 초기화 함수 호출
    srand( (unsigned)time(NULL) );
    
    // 0. opening_게임시작
    opening();
    
    // 1. 초기화 & 플레이어 이름 결정
    board_initBoard();
    
    // 2. 반복문 (플레이어 턴)
    do {
        int step = rolldie();
        int coinResult;
        char c;
        
        board_printBoardStatus();
        
        pos += step;
        coinResult = board_getBoardCoin(pos);
        
        printf("press any key to continue:");
        scanf("%s", &c);
        fflush(stdin);
        // 2-1. 플레이어의 상태 출력
        // 2-2. 주사위 던지기
        // 2-3. 이동
        // 2-4. 동전 줍기
        // 2-5. 다음턴
        // 2-6. if( 조건: 모든 플레이어가 한번 씩 턴을 돈다)
        // 상어동작
    } while(1);
    
    // 3. 정리 (승자 계산, 출력 등)
    /*printf("\n\n\n\n\n\n\n\n\n\n");
    printf("=====================================================\n");
    printf("*****************************************************\n");
    printf("                  CONGRATULATION!!!!!                \n");
    printf("*#&$*#^&*$&^@($!@(*   BINGO!!!!!   #)!@*(#)*%$(#*)@*(\n");
    printf("                      YOU WIN!!!!!                   \n");
    printf("*****************************************************\n");
    printf("=====================================================\n\n");
    */
    return 0;
}
