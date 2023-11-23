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

#define MAX_CHARNAME    200
#define MAX_DIE     6
#define N_PLAYER    3

#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2

int     player_position[N_PLAYER];
char    player_name[N_PLAYER][MAX_CHARNAME];
int     player_coin[N_PLAYER];
int     player_status[N_PLAYER];        // 0, 1, 2 중 하나
char    player_statusString[3][MAX_CHARNAME] = {"LIVE","DIE","END"};


//--------------------시작함수---------------------------
void opening(void)
{
    printf("=====================================================\n");
    printf("*****************************************************\n");
    printf("                        SHARK GAME                   \n");
    printf("*****************************************************\n");
    printf("=====================================================\n\n\n");
}


int rolldie(void)
{
    return rand()%MAX_DIE+1;
}

// --------------------player위치 출력----------------------------------
void printPlayerPosition(int Player)
{
    int i;
    for(i=0; i<N_BOARD; i++)
    {
        printf("|");
        if (player_position[Player] == i)
            printf("%c", player_name[Player][0]);
        else
        {
            if (board_getBoardStatus(i) == BOARDSTATUS_NOK)
                printf("X");
            else
                printf(" ");
        }
    }
    printf("|\n");
}

// ------------------player상태 출력 함수--------------------------------
void printPlayerStatus(void)
{
    int i;
    printf("----------------player status -------------\n");
    for (i=0; i<N_PLAYER; i++)
    {
        printf("%s : position %i, coin %i, status: %s \n",
               player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
    }
    printf("-------------------------------------------\n");
}

// -----------------------------------------------------------
void checkDie(void)
{
    int i;
    for(i=0; i<N_PLAYER; i++)
        if(board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
        {
            player_status[i] = PLAYERSTATUS_DIE;
            printf("player %s 는 상어한테 죽었네용 ㅜㅜ\n", player_name[i]);
        }
}

// ---------------------게임종료--------------------------------
int game_end(void)
{
    int i;
    int flag_end = 1;
    
    // if all player die?
    for(i=0; i<N_PLAYER; i++)
    {
        if(player_status[i] == PLAYERSTATUS_LIVE)
        {
            flag_end =0;
            break;
        }
    }
    return flag_end;
}

int getAlivePlayer(void)
{
    int i;
    int cnt=0;
    for(i=0; i<N_PLAYER; i++)
    {
        if(player_status[i] == PLAYERSTATUS_END)
            cnt++;
    }
    return cnt;
}

int getWinnner(void)
{
    int i;
    int winner=0;
    int max_coin=-1;
    for(i=0; i<N_PLAYER;i++)
    {
        if(player_coin[i] > max_coin)
        {
            max_coin = player_coin[i];
            winner = i;
        }
    }
    return winner;
}
// -----------------------main 함수----------------------------------
int main(void)
{
    int pos = 0;
    int i;
    int turn = 0;   // 0    0번째 플레이어부터 시작할거임
    // rand 초기화 함수 호출
    srand( (unsigned)time(NULL) );
    
    // ==========0. opening_게임시작==========
    opening();
    
    // ==========1. 초기화 & 플레이어 이름 결정==========
    board_initBoard();
    // 1-2.
    for (i=0; i<N_PLAYER; i++)
    {
        player_position[i] = 0;
        player_coin[i] = 0;
        player_status[i] = PLAYERSTATUS_LIVE;
        // player name
        printf("PLayer %i's name: ", i);
        scanf("%s", player_name[i]);        // 자체가 포인터여서 &필요없음
    }
    
    
    // 2. ==========반복문 (플레이어 턴)==========
    do {
        
        int coinResult;
        char c;
        int step;
        
        // player가 살아있는 경우가 아니면 다음턴으로 넘어감
        if(player_status[turn] != PLAYERSTATUS_LIVE)
        {
            turn = (turn + 1)%N_PLAYER;
            continue;;
        }
        // -----2-1. 플레이어의 상태 출력-----
        board_printBoardStatus();
        for(i=0; i<N_PLAYER; i++)
        {
            printPlayerPosition(i);
        }
        printPlayerStatus();
        
        
        // -----2-2. 주사위 던지기-----
        printf("\n\n\n%s turn!", player_name[turn]);
        printf("press any key to continue:");
        scanf("%s", &c);
        fflush(stdin);
        step = rolldie();
        
        
        // --------2-3. 이동---------
        player_position[turn] += step;
        if (player_position[turn] >= N_BOARD)
        {
            player_position[turn] = N_BOARD-1;
        }
        if (player_position[turn] == N_BOARD-1)
        {
            player_status[turn] = PLAYERSTATUS_END;
            printf("player %s는 끝났네용~~", player_name[turn]);
        }
        
        
        
        // ---------2-4. 동전 줍기------
        coinResult = board_getBoardCoin(pos);
        player_coin[turn] += coinResult;
        printf("\n\nplayer %s 는 동전을 %i개 줍고, 지금 %i개 가지고 있네요!\n", player_name[turn], coinResult, player_coin[turn]);
        
        
        // 2-5. 다음턴
        turn = (turn + 1)%N_PLAYER; // wrap around: 플레이어 숫자가 되는 순간 다시 돌아가
        
        
        // 2-6. if( 조건: 모든 플레이어가 한번 씩 턴을 돈다)
        
        if (turn == 0)
        {
            // 상어동작
            int shark_pos = board_stepShark();
            printf("Shark는 %i로 이동했다 77ㅑ~~\n", shark_pos);
            checkDie();
        }
        
    } while(game_end() == 0);
    
    // 3. 정리 (승자 계산, 출력 등)
    int winner=getWinnner();
    int Alive=getAlivePlayer();
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("=====================================================\n");
    printf("                     %i명이 생존했군요~~                 \n", Alive);
    printf("*****************************************************\n");
    printf("                  CONGRATULATION!!!!!                \n");
    printf("********************    BINGO!!!!!   ****************\n");
    printf("                      player %s Win!!!!!             \n", player_name[winner]);
    printf("*****************************************************\n");
    printf("=====================================================\n\n");
    
    return 0;
}
