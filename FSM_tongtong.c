#include <stdio.h>
#include <windows.h>
int g_max_num;
// Define events
enum{

    No_1_penguin,
    No_2_penguin,
    No_3_penguin,
    No_4_penguin,
    No_5_penguin,
    No_n_penguin,
    TonTon_penguin,
};
// Define events need to be trigger
enum{

    EVENT1 = 1,
    EVENT2,
    EVENT3,
    EVENT4,
    EVENT5,
    EVENT6,
    EVENT7,
};
// Define the data struct of state-table
typedef struct FsmTable_s{

    int event;
    int CurState;
    void (*eventAcFun)();
    int NextState;
}FsmTable_t;

typedef struct FSM_s{
    
    FsmTable_t* FsmTable;
    int curState;
}FSM_t;

void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable){

    pFsm -> FsmTable = pTable;
}

void FSM_StateTransfer(FSM_t* pFsm, int state){

    pFsm -> curState = state;
}

void FSM_EventHandle(FSM_t* pFsm, int event){

    FsmTable_t* pActTable = pFsm -> FsmTable;
    void (*eventActFun)()=NULL; //function point 初始化
    int NextState;
    int CurState = pFsm -> curState;
    int flag = 0;
    //獲取當前狀態
    for (int i = 0; i < g_max_num; i++){
        //當前狀態指定的事件我才執行他
        if (event==pActTable[i].event){
            
            if (CurState == pActTable[i].CurState){
                
                flag = 1;
                eventActFun = pActTable[i].eventAcFun;
                NextState = pActTable[i].NextState;
                break;
            }
        }
    }
    
    if(flag){ //條件滿足的狀態下
        //action
        if(eventActFun){

            eventActFun();
        }
        //跳轉到下一個狀態
        FSM_StateTransfer(pFsm, NextState);
    }

    else
    {
        
    }
}

void GetNo_1_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetNo_2_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetNo_3_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetNo_4_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetNo_5_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetNo_n_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping and hitting TonTon. \n\n");
}

void GetTonTon_penguin(){

    printf("What are your hobbies?. \n");
    printf("eating,sleeping. \n\n");
    printf("Why don't you like hitting TonTon. \n\n");
    printf("...I am TonTon.\n\n");
}
// Define the state-table of FSM
FsmTable_t Table[]={

    {EVENT1, No_1_penguin,GetNo_1_penguin,No_2_penguin},
    {EVENT2, No_2_penguin,GetNo_2_penguin,No_3_penguin},
    {EVENT3, No_3_penguin,GetNo_3_penguin,No_4_penguin},
    {EVENT4, No_4_penguin,GetNo_4_penguin,No_5_penguin},
    {EVENT5, No_5_penguin,GetNo_5_penguin,No_n_penguin},
    {EVENT6, No_n_penguin,GetNo_n_penguin,TonTon_penguin},
    {EVENT7, TonTon_penguin,GetTonTon_penguin,No_1_penguin},
};
// Stete Machine regist and state transferation
void InitFsm(FSM_t* pFsm){

    g_max_num = sizeof(Table) / sizeof(FsmTable_t);
    pFsm -> curState = No_1_penguin;
    FSM_Regist(pFsm, Table);
}

void polling_day(int *event){

    if(*event == 7){
        
        *event=1;
    }

    else
    {
        (*event)++;
    }
}

int main(){

    FSM_t fsm;
    InitFsm(&fsm);
    int event =EVENT1;

    while (1)
    {
        //printf("event %d is coming...\n",event);
        FSM_EventHandle(&fsm,event);
        //printf("fsm current state %d\n",fsm.curState);
        polling_day(&event);
        Sleep(3000);
    }
    
    return 0;
}

