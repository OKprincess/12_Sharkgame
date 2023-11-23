//
//  gameboard.c
//  12
//
//  Created by ok sojoung on 2023/11/21.
//

#include "gameboard.h"
#include <stdio.h>
#include <stdlib.h>

//#define N_BOARD        15
#define N_COINPOS      12
#define MAX_COIN        4

#define MAX_SHARKSTEP   6
#define SHARK_INITPOS   -4

// 필요한 변수 전역변수로 정의
static int board_status[N_BOARD];   // 몇번째 칸의 파손여부
static int board_coin[N_BOARD];     // i번째 칸의 동전개수

static int board_sharkPosition;     // 상어의 위치저장

// ------------------------------------------------------------------
// board status와 coin 초기화
int board_initBoard(void)
{
    int i;
    for(i=0; i<N_BOARD; i++)
    {
        // board_status의 i번째 요소 0설정
        board_status[i] = BOARDSTATUS_OK;
        
        // board_coin의 i번째 요소 0 설정
        board_coin[i] = 0;
    }
    
    board_sharkPosition = SHARK_INITPOS;
    //coin 할당
    for(i=0; i<N_COINPOS; i++)
    {
        int flag = 0;
        //i번째 코인이 할당되지 않으면 반복
        while (flag == 0)
        {
            //동전을 놓을 칸을 랜덤으로 지정
            int allocPos = rand()%N_BOARD;
            if(board_coin[allocPos] == 0)   // allcPos가 0이면 할당안된 것
               {
                   // i번째 coin할당
                   board_coin[allocPos] = rand()%MAX_COIN+1;
                   flag = 1;
               }
        }
    }
    
    return 0;
}

// ------------------------------------------------------------
// board 판 만들어주기
int board_printBoardStatus(void)
{
    int i;
    printf("-------------------- BOARD STATUS --------------------\n");
    for(i=0; i<N_BOARD; i++)
    {
        printf("|");
        if(board_status[i] == BOARDSTATUS_NOK)
            printf("X");
        else
            printf("O");
    }
    printf("|\n");
    printf("======================================================\n");
    
    return 0;
}

// -----------------------------------------------------------------
int board_getBoardStatus(int pos)
{
    return board_status[pos];
}

// ------------------------------------------------------------------
int board_getBoardCoin(int pos)
{
    int coin = board_coin[pos];
    board_coin[pos] = 0;
    return coin;
}

// --------------------------------------------------------------------
int board_stepShark(void)
{
    int  step = rand()%MAX_SHARKSTEP + 1;
    int i;
    for(i=board_sharkPosition+1; i<=board_sharkPosition+step; i++)
    {
        if (i>= 0 && i < N_BOARD)
            board_status[i] = BOARDSTATUS_NOK;
    }
    board_sharkPosition += step;
    
    return board_sharkPosition;
}
