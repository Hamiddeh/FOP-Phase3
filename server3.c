#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

//Functions

int PrepareToGet();
int PreProcess();
int AnsToClient(int,int);
int GetOrder(int,int);
int Process(int,int);
int Regist();
int Login();
int Members();
int Send();
int Logout();
int Leave();
int Create();
int Create_P();
int Join();
int Refresh();
int Channel_Pass();
int Tabdil(int);
int ANS(char[],char[]);
int ANS2(char[],char[]);
int find_char(char s[10000],char ch);
int Token();
int tok_eq(char[]);
int tok_check();
int tok_em(int);
int us_check(char[]);
int andis(char[]);
char* Tabdil2(char ord[10000] ,int n);
int GetASM(char aray[10000]);
char* GetAM(char aray[10000],int i);
char* GetA(char aray[10000],int i);
int GetAS(char aray[10000]);
char* GetO(char* object,char item[10000]);
char* createS(char* str);
char* createA();
char* createO();
int AddIA(char* aray, char* item);
int AddIO(char* object, char* item, char* value);
int DelIA(char[],int);
int DelIAM(char[],int);
int Srch_M();
int Srch_U();
int EX(char*);
int Poi(char*,char*);

//Globals

char canal[10000][10000]; //clients are joined
char kanal[10000][10000]; //clients want to join
char user_online[10000][10000];
char user[10000];
char order[10000];
char Answer[10000];
char autoken[10000][10000];
int tokCount=0;
int usCount=0;
int refc[10000]={0};
char rub[10000];
char rub2[10000];
char rub3[10000];
char rub4[10000];
char rub5[10000];
char rub6[10000];

//Main

int main()
{
    int i;
    for(i=0;i<10000;i++){
        memset(autoken,0,10000);memset(canal,0,10000);memset(user_online,0,10000);
    }
    srand(time(NULL));
    PreProcess();
    return 0;
}

// Kind 1
int PreProcess()
{
    PrepareToGet();
    PreProcess();
}
int PrepareToGet()
{
    int server_socket, client_socket;
    struct sockaddr_in server, client;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    server_socket = socket(AF_INET, SOCK_STREAM, 6);
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(12345);
    bind(server_socket, (struct sockaddr *)&server, sizeof(server));
    listen(server_socket, 5);
    printf("IS LISTENING....\n");
    int len = sizeof(client);
    client_socket = accept(server_socket, (struct sockaddr *)&client, &len);
    GetOrder(client_socket,server_socket);
}
int GetOrder(int client_socket,int server_socket)
{
    memset(order,0,10000);
    recv(client_socket, order, 10000, 0);
    printf("%s",order);
    Process(client_socket,server_socket);
}
int AnsToClient(int client_socket,int server_socket)
{
    printf("%s\n",Answer);
    send(client_socket,Answer,10000,0);
    closesocket(server_socket);
}
int Process(int client_socket,int server_socket)
{
    if(strncmp(order,"register",8)==0)
    {
        Regist();
    }
    else if(strncmp(order,"login",5)==0)
    {
        Login();
    }
    else if(strncmp(order,"create channel_p",16)==0)
    {
        Create_P();
    }
    else if(strncmp(order,"create channel",14)==0)
    {
        Create();
    }
    else if(strncmp(order,"join channel",12)==0)
    {
        Join();
    }
    else if(strncmp(order,"send",4)==0)
    {
        Send();
    }
    else if(strncmp(order,"refresh",7)==0)
    {
        Refresh();
    }
    else if(strncmp(order,"leave",5)==0)
    {
        Leave();
    }
    else if(strncmp(order,"channel members",15)==0)
    {
        Members();
    }
    else if(strncmp(order,"logout",6)==0)
    {
        Logout();
    }
    else if(strncmp(order,"channel pass",12)==0)
    {
        Channel_Pass();
    }
    else if(strncmp(order,"search_M",8)==0)
    {
        Srch_M();
    }
    else if(strncmp(order,"search_U",8)==0)
    {
        Srch_U();
    }
    else
    {
        ANS("Error","Undefined order");
    }
    AnsToClient(client_socket,server_socket);
}

//Kind 2
int Regist()
{
    int A=0;
    char User[10000],Pass[10000],s[10000],p[10000];
    memset(User,0,10000);memset(Pass,0,10000);memset(p,0,10000);memset(s,0,10000);
    Tabdil(9);
    strncpy(User,order,find_char(order,','));
    Tabdil(strlen(User)+2);
    strncpy(Pass,order,strlen(order)-1);
    FILE *UP;
    strcpy(s,"Resources/Users/");
    strcat(s,User);
    strcat(s,".txt");
    UP=fopen(s,"r");
    if(UP==NULL)
    {
        fclose(UP);
        char us[10000];memset(us,0,10000);
        strcpy(us,createO());
        printf("%s\n",User);
        AddIO(us,"Username",createS(User));
        AddIO(us,"Password",createS(Pass));
        UP=fopen(s,"w");
        fputs(us,UP);
        ANS("Successful","");
        fclose(UP);
    }
    else
    {
        fclose(UP);
        ANS("Error","The Username is not unique");
    }
}
int Login()
{
    int A=0;
    char User[10000],Pass[10000],s[10000],p[10000],b[10000];
    memset(User,0,10000);memset(Pass,0,10000);memset(p,0,10000);memset(s,0,10000);memset(b,0,10000);
    strcpy(Pass,"\"");
    Tabdil(6);
    strncpy(User,order,find_char(order,','));
    Tabdil(strlen(User)+2);
    strncat(Pass,order,strlen(order)-1);
    strcat(Pass,"\"");
    FILE *UP;
    strcat(s,"Resources/Users/");
    strcat(s,User);
    strcat(s,".txt");
    UP=fopen(s,"r");
    if(UP==NULL)
    {
        ANS("Error","The Username doesn't exist");
    }
    else
    {
        while(!feof(UP)){
            strcat(p,fgets(b,10000,UP));
            memset(b,0,10000);
        }
        char us[10000];memset(us,0,10000);
        strcpy(us,p);
        fclose(UP);
        char ps[10000];memset(ps,0,10000);
        strcpy(ps,GetO(us,"Password"));
        if(strcmp(ps,Pass)==0)
        {
            if(us_check(User)==0)
                ANS("Error","User hasn't log out");
            else{
                Token();
                strcpy(user_online[usCount],User);
                usCount++;
                ANS("AuthToken",autoken[tokCount-1]);
            }
        }
        else
            ANS("Error","Wrong Password");
    }

}
int Logout()
{
    char tok[10000];
    memset(tok,0,10000);
    Tabdil(7);
    strcpy(tok,order);
    int i,A=0;
    for(i=0;i<tokCount;i++)
    {
        if(strncmp(tok,autoken[i],strlen(autoken[i]))==0)
        {
            A=1;
            ANS("Successful","");
            memset(autoken[i],0,10000);
            memset(user_online[i],0,10000);
            tok_em(i);
            break;
        }
    }
    if(A==0)
        ANS("Error","Your token is wrong");
}
int Join()
{
    int A=0,i,k;
    char ch_N[10000],tok[10000],s[10000],p[10000],q[10000],b[10000];
    memset(tok,0,10000);memset(ch_N,0,10000);memset(p,0,10000);memset(s,0,10000);memset(q,0,10000);
    Tabdil(13);
    strncpy(ch_N,order,find_char(order,','));
    Tabdil(strlen(ch_N)+2);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,ch_N);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        ANS("Error","The channel doesn't exist");
    }
    else
    {
        while(!feof(ch)){
            strcat(p,fgets(b,10000,ch));
            memset(b,0,10000);
        }
        fclose(ch);
        char cn[10000],mem[10000],mes[10000];memset(cn,0,10000);memset(mem,0,10000);memset(mes,0,10000);
        strcpy(cn,p);
        strcpy(mem,GetO(cn,"Members"));
        strcpy(mes,GetO(cn,"Messeges"));
        int i,k=0;
        char us[10000];memset(us,0,10000);
        strcpy(us,"\"");
        strcat(us,user);
        strcat(us,"\"");
        for(i=0;i<GetASM(mem);i++)
        {
            char submem[10000];memset(submem,0,10000);
            strcpy(submem,GetAM(mem,i));
            if(strcmp(submem,us)==0)
            {
                k=1;
                ANS("Error","The user has joined before");
                break;
            }
        }
        if(k==0)
        {
            char PS[10000];memset(PS,0,10000);
            strcpy(PS,GetO(cn,"Password"));
            if(strcmp(PS,"\"NULL\"")==0)
            {
                char submes[10000];memset(submes,0,10000);
                AddIA(mem,createS(user));
                strcpy(submes,createO());
                AddIO(submes,"sender",createS(user));
                strcpy(q,user);strcat(q," joined the channel");
                AddIO(submes,"content",createS(q));
                AddIA(mes,submes);
                char cn2[10000];memset(cn2,0,10000);strcpy(cn2,createO());
                AddIO(cn2,"Name",GetO(cn,"Name"));
                AddIO(cn2,"Password",GetO(cn,"Password"));
                AddIO(cn2,"Members",mem);
                AddIO(cn2,"Messeges",mes);
                strcpy(cn,cn2);
                printf("%s\n",cn);
                ch=fopen(s,"w");
                fputs(cn,ch);
                fclose(ch);
                strcpy(canal[andis(user)],ch_N);
                ANS("Successful","");
            }
            else
            {
                strcpy(kanal[andis(user)],ch_N);
                ANS("Private channel","Enter Password");
            }
        }
    }
}
int Create()
{
    int A=0;
    char ch_N[10000],tok[10000],s[10000],p[10000],b[10000];
    memset(tok,0,10000);memset(ch_N,0,10000);memset(p,0,10000);memset(s,0,10000);
    Tabdil(15);
    strncpy(ch_N,order,find_char(order,','));
    Tabdil(strlen(ch_N)+2);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,ch_N);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        char cn[10000],mes[10000],mem[10000],submes[10000];memset(cn,0,10000);memset(submes,0,10000);memset(mes,0,10000);memset(mem,0,10000);
        strcpy(cn,createO());
        AddIO(cn,"Name",createS(ch_N));
        AddIO(cn,"Password",createS("NULL"));
        strcpy(mes,createA());
        strcpy(mem,createA());
        AddIA(mem,createS(user));
        strcpy(submes,createO());
        AddIO(submes,"sender",createS(user));
        char q[10000];
        strcpy(q,user);
        strcat(q," created the channel");
        AddIO(submes,"content",createS(q));
        AddIA(mes,submes);
        AddIO(cn,"Members",mem);
        AddIO(cn,"Messeges",mes);
        ch=fopen(s,"w");
        fputs(cn,ch);
        fclose(ch);
        strcpy(canal[andis(user)],ch_N);
        ANS("Successful","");
    }
    else
    {
        fclose(ch);
        ANS("Error","The channel has existed before");
    }
}
int Create_P()
{
    int A=0;
    char ch_N[10000],tok[10000],s[10000],p[10000],b[10000],pass[10000];
    memset(tok,0,10000);memset(ch_N,0,10000);memset(p,0,10000);memset(s,0,10000);memset(pass,0,10000);
    Tabdil(17);
    strncpy(ch_N,order,find_char(order,','));
    Tabdil(strlen(ch_N)+2);
    strncpy(pass,order,find_char(order,','));
    Tabdil(strlen(pass)+2);
    strcpy(tok,order);
    printf("%s\n",tok);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,ch_N);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        char cn[10000],mes[10000],mem[10000],submes[10000];memset(cn,0,10000);memset(mes,0,10000);memset(mem,0,10000);memset(submes,0,10000);
        strcpy(cn,createO());
        AddIO(cn,"Name",createS(ch_N));
        AddIO(cn,"Password",createS(pass));
        strcpy(mes,createA());
        strcpy(mem,createA());
        AddIA(mem,createS(user));
        strcpy(submes,createO());
        AddIO(submes,"sender",createS(user));
        char q[10000];
        strcpy(q,user);
        strcat(q," created the channel");
        AddIO(submes,"content",createS(q));
        AddIA(mes,submes);
        AddIO(cn,"Members",mem);
        AddIO(cn,"Messeges",mes);
        ch=fopen(s,"w");
        fputs(cn,ch);
        fclose(ch);
        strcpy(canal[andis(user)],ch_N);
        ANS("Successful","");
    }
    else
    {
        fclose(ch);
        ANS("Error","The channel has existed before");
    }
}
int Leave()
{
    char tok[10000],s[10000],p[10000],b[10000];
    memset(tok,0,10000);memset(p,0,10000);memset(s,0,10000);
    Tabdil(6);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,canal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        ANS("Error","The channel doens't exist");
    }
    else
    {
        int o=0;
        while(!feof(ch)){
            strcat(p,fgets(b,10000,ch));
            memset(b,0,10000);
        }
        char cn[10000],mem[10000],mes[10000],su[10000];memset(cn,0,10000);memset(mes,0,10000);memset(mem,0,10000);memset(su,0,10000);
        strcpy(cn,p);
        strcpy(mem,GetO(cn,"Members"));
        strcpy(mes,GetO(cn,"Messeges"));
        strcpy(su,createO());
        int i;
        char us[10000];
        strcpy(us,"\"");
        strcat(us,user);
        strcat(us,"\"");
        for(i=0;i<GetASM(mem);i++)
        {
            if(strcmp(us,GetAM(mem,i))==0)
            {
               o=1;
               char h[10000];
               strcpy(h,user);
               strcat(h," leaved the channel");
               AddIO(su,"sender",createS(user));
               AddIO(su,"content",createS(h));
               AddIA(mes,su);
               DelIAM(mem,i);
               break;
            }
        }
        if(o==0)
            ANS("Error","The user is not joined in the channel");
        else{
            char cn2[10000];memset(cn2,0,10000);strcpy(cn2,createO());
            AddIO(cn2,"Name",GetO(cn,"Name"));
            AddIO(cn2,"Password",GetO(cn,"Password"));
            AddIO(cn2,"Members",mem);
            AddIO(cn2,"Messeges",mes);
            strcpy(cn,cn2);
            ch=fopen(s,"w");
            fputs(cn,ch);
            fclose(ch);
            memset(canal[andis(user)],0,10000);
            refc[andis(user)]=0;
            ANS("Successful","");
        }
    }
}
int Send()
{
    char tok[10000],s[10000],p[10000],payam[10000],b[10000];
    memset(tok,0,10000);memset(s,0,10000);memset(p,0,10000);memset(payam,0,10000);
    Tabdil(5);
    strncpy(payam,order,find_char(order,','));
    Tabdil(strlen(payam)+2);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,canal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        ANS("Error","The channel doesn't exist");
    }
    else
    {
        while(!feof(ch)){
            strcat(p,fgets(b,10000,ch));
            memset(b,0,10000);
        }
        char cn[10000],mes[10000],submes[10000];memset(cn,0,10000);memset(submes,0,10000);memset(mes,0,10000);
        strcpy(cn,p);
        strcpy(mes,GetO(cn,"Messeges"));
        strcpy(submes,createO());
        AddIO(submes,"sender",createS(user));
        AddIO(submes,"content",createS(payam));
        AddIA(mes,submes);
        char cn2[10000];memset(cn2,0,10000);strcpy(cn2,createO());
        AddIO(cn2,"Name",GetO(cn,"Name"));
        AddIO(cn2,"Password",GetO(cn,"Password"));
        AddIO(cn2,"Members",GetO(cn,"Members"));
        AddIO(cn2,"Messeges",mes);
        strcpy(cn,cn2);
        fclose(ch);
        ch=fopen(s,"w");
        fputs(cn,ch);
        fclose(ch);
        ANS("Successful","");
    }
}
int Refresh()
{
    char tok[10000],s[10000],p[10000],b[10000];
    memset(tok,0,10000);memset(s,0,10000);memset(p,0,10000);
    Tabdil(8);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,canal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        ANS("Error","The channel doesn't exist");
    }
    else
    {
        while(!feof(ch)){
            strcat(p,fgets(b,10000,ch));
            memset(b,0,10000);
        }
        fclose(ch);
        char cn[10000],mes[10000],ms[10000];memset(cn,0,10000);memset(mes,0,10000);memset(ms,0,10000);
        int i,j;
        strcpy(cn,p);
        strcpy(ms,createA());
        strcpy(mes,GetO(cn,"Messeges"));
        for(i=refc[andis(user)];i<GetAS(mes);i++)
            AddIA(ms,GetA(mes,i));
        refc[andis(user)]=GetAS(mes);
        ANS2("List",ms);
    }
}
int Members()
{
    char tok[10000],s[10000],p[10000],b[10000];
    memset(tok,0,10000);memset(s,0,10000);memset(p,0,10000);
    Tabdil(16);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,canal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        ANS("Error","The channel doesn't exist");
    }
    else
    {
        while(!feof(ch)){
            strcat(p,fgets(b,10000,ch));
            memset(b,0,10000);
        }
        fclose(ch);
        char cn2[10000],cn[10000],mem[10000],mem2[10000],mmm[10000];memset(cn,0,10000);memset(mem,0,10000);memset(cn2,0,10000);
        int i;
        strcpy(cn,p);
        strcpy(cn2,createO());
        strcpy(mem,GetO(cn,"Members"));
        strcpy(mmm,createA());
        for(i=0;i<GetASM(mem);i++)
        {
            if(EX(GetAM(mem,i))==1)
            {
                strcpy(mem2,GetAM(mem,i));
                AddIA(mmm,mem2);
            }
        }
        AddIO(cn2,"Name",GetO(cn,"Name"));
        AddIO(cn2,"Password",GetO(cn,"Password"));
        AddIO(cn2,"Members",mmm);
        AddIO(cn2,"Messeges",GetO(cn,"Messeges"));
        strcpy(cn,cn2);
        ch=fopen(s,"w");
        fputs(cn,ch);
        fclose(ch);
        ANS2("List",mmm);
    }
}
int Channel_Pass()
{
    char tok[10000],pass[10000],pas2[10000],s[10000],p[10000],b[10000];
    memset(tok,0,10000);memset(pass,0,10000);memset(s,0,10000);memset(p,0,10000);
    strcpy(pas2,"\"");
    Tabdil(13);
    strncpy(pass,order,find_char(order,','));
    Tabdil(strlen(pass)+2);
    strcpy(tok,order);
    int i;
    if(tok_eq(tok)==0)
        return 0;
    strcat(pas2,pass);
    strcat(pas2,"\"");
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,kanal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    while(!feof(ch))
        strcat(p,fgets(b,10000,ch));
    fclose(ch);
    char cn[10000];memset(cn,0,10000);
    strcpy(cn,p);
    if(strcmp(pas2,GetO(cn,"Password"))==0)
    {
        char q[10000];
        char submes[10000],mem[10000],mes[10000];memset(submes,0,10000);memset(mes,0,10000);memset(mem,0,10000);
        strcpy(mem,GetO(cn,"Members"));
        strcpy(mes,GetO(cn,"Messeges"));
        AddIA(mem,createS(user));
        strcpy(submes,createO());
        AddIO(submes,"sender",createS(user));
        strcpy(q,user);strcat(q," joined the channel");
        AddIO(submes,"content",createS(q));
        AddIA(mes,submes);
        char cn2[10000];memset(cn2,0,10000);strcpy(cn2,createO());
        AddIO(cn2,"Name",GetO(cn,"Name"));
        AddIO(cn2,"Password",GetO(cn,"Password"));
        AddIO(cn2,"Members",mem);
        AddIO(cn2,"Messeges",mes);
        strcpy(cn,cn2);
        ch=fopen(s,"w");
        fputs(cn,ch);
        fclose(ch);
        strcpy(canal[andis(user)],kanal[andis(user)]);
        ANS("Successful","");
    }
    else
    {
        ANS("Error","Wrong password");
    }
}
int Srch_M()
{
    char tok[10000],s[10000],p[10000],PM[10000],b[10000];
    memset(tok,0,10000);memset(s,0,10000);memset(p,0,10000);memset(PM,0,10000);
    Tabdil(9);
    printf("%s\n",order);
    strncpy(PM,order,find_char(order,','));
    printf("%s\n",order);
    Tabdil(strlen(PM)+2);
    printf("%s\n",order);
    strcpy(tok,order);
    if(tok_eq(tok)==0)
        return 0;
    FILE *ch;
    strcat(s,"Resources/Channels/");
    strcat(s,canal[andis(user)]);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
    {
        fclose(ch);
        ANS("Error","The channel doesn't exist");
    }
    else
    {
        fgets(p,10000,ch);
        char cn[10000],mes[10000],sss[10000],sd[10000];memset(cn,0,10000);memset(mes,0,10000);
        strcpy(cn,p);
        strcpy(b,createA());
        strcpy(mes,GetO(cn,"Messeges"));
        int i;
        for(i=0;i<GetAS(mes);i++)
        {
            strcpy(sss,GetA(mes,i));
            if(Poi(GetO(sss,"content"),PM)==1)
            {
                strcpy(sd,GetA(mes,i));
                AddIA(b,GetO(sd,"content"));
            }
        }
        ANS2("List",b);
    }
}
int Srch_U()
{
    char tok[10000],s[10000],p[10000],UN[10000],b[10000];
    memset(tok,0,10000);memset(s,0,10000);memset(p,0,10000);memset(UN,0,10000);
    Tabdil(9);
    strncpy(UN,order,strlen(order)-1);
    FILE *ch;
    strcpy(s,"Resources/Users/");
    strcat(s,UN);
    strcat(s,".txt");
    ch=fopen(s,"r");
    if(ch==NULL)
        ANS("Response","This username doesn't exist");
    else
        ANS("Response","This username exists");
}
//Kind 3
int ANS(char type[],char content[])
{
    char awer[10000];memset(awer,0,10000);
    strcpy(awer,createO());
    AddIO(awer,"type",createS(type));
    AddIO(awer,"content",createS(content));
    strcpy(Answer,awer);
}
int ANS2(char type[],char content[])
{
    char awer[10000];memset(awer,0,10000);
    strcpy(awer,createO());
    AddIO(awer,"type",createS(type));
    AddIO(awer,"content",content);
    strcpy(Answer,awer);
}

//Kind 4
int Token()
{
    int i;
    do{
        for(i=0;i<20;i++)
            autoken[tokCount][i]=rand()%41+50;
    }
    while(tok_check()==0);
    tokCount++;
}
int tok_eq(char s[10000])
{
    int i;
    s[strlen(s)-1]=NULL;
    for(i=0;i<tokCount;i++)
    {
        if(strcmp(s,autoken[i])==0)
        {
            memset(user,0,10000);
            strcpy(user,user_online[i]);
            return 1;
        }
    }
    ANS("Error","Your token is wrong");
    return 0;
}
int tok_em(int i)
{
    int j;
    for(j=i;j<tokCount;j++)
    {
        strcpy(autoken[j],autoken[j+1]);
        strcpy(user_online[j],user_online[j+1]);
        strcpy(canal[j],canal[j+1]);
        strcpy(kanal[j],kanal[j+1]);
        refc[j]=refc[j+1];
    }
    tokCount--;
    usCount--;
}
int tok_check()
{
    int i=0,j=0;
    for(;i<tokCount;i++)
        for(j=i+1;j<tokCount;j++)
            if(strcmp(autoken[i],autoken[j])==0)
                return 0;
    return 1;
}
int us_check(char s[10000])
{
    int i=0;
    for(;i<usCount;i++)
        if(strcmp(s,user_online[i])==0)
            return 0;
    return 1;
}
int andis(char s[])
{
    int i;
    for(i=0;i<usCount;i++)
        if(strcmp(s,user_online[i])==0)
            return i;
}
//kind 5
int AddIO(char object[1000], char item[1000], char value[1000])
{
    strcpy(rub5,value);
    memset(rub,0,1000);
    strncpy(rub,object,strlen(object)-1);
    memset(rub2,0,1000);
    strcpy(rub2,"\"");
    strcat(rub2,item);
    strcat(rub2,"\":");
    strcat(rub2,rub5);
    if(strlen(rub)>1)
        strcat(rub,", ");
    strcat(rub,rub2);
    strcat(rub,"}");
    strcpy(object,rub);
}
int AddIA(char* aray, char* item)
{
    strcpy(rub5,item);
    memset(rub,0,10000);
    strncpy(rub,aray,strlen(aray)-1);
    if(strlen(rub)>1)
        strcat(rub,", ");
    strcat(rub,rub5);
    strcat(rub,"]");
    strcpy(aray,rub);
}
char* createO()
{
    memset(rub,0,10000);
    strcpy(rub,"{}");
    return rub;
}
char* createA()
{
    memset(rub,0,10000);
    strcpy(rub,"[]");
    return rub;
}
char* createS(char* str)
{
    memset(rub,0,10000);
    strcpy(rub,"\"");
    strcat(rub,str);
    strcat(rub,"\"");
    return rub;
}
char* GetO(char* object,char item[10000])
{
    int i,j;
    memset(rub,0,10000);memset(rub2,0,10000);memset(rub3,0,10000);memset(rub4,0,10000);memset(rub5,0,10000);
    strcpy(rub,"\"");
    strcat(rub,item);
    strcat(rub,"\":");
    strcpy(rub2,strstr(object,rub));
    strcpy(rub2,Tabdil2(rub2,strlen(rub)));
    if((find_char(rub2,'"')<find_char(rub2,'[') && find_char(rub2,'"')!=-1) || find_char(rub2,'[')==-1)
    {
        strcpy(rub2,strchr(rub2,'"'));
        rub3[0]=rub2[0];
        for(i=1;rub2[i]!='"';i++)
            rub3[i]=rub2[i];
        rub3[i]=rub2[i];
        return rub3;
    }
    else
    {
        strcpy(rub2,strchr(rub2,'['));
        strcpy(rub3,rub2);
        i=1;
        strcpy(rub2,Tabdil2(rub2,1));
        int co=0;
        while(i!=0)
        {
            if(find_char(rub2,'[')<find_char(rub2,']') && find_char(rub2,'[')!=-1)
            {
                i++;
                co+=find_char(rub2,'[');
                strcpy(rub2,strchr(rub2,'['));
                strcpy(rub2,Tabdil2(rub2,1));
            }
            else if(find_char(rub2,']')<find_char(rub2,'[') && find_char(rub2,']')!=-1)
            {
                i--;
                co+=find_char(rub2,']');
                strcpy(rub2,strchr(rub2,']'));
                strcpy(rub2,Tabdil2(rub2,1));
            }
            else if(find_char(rub2,'[')!=-1 && find_char(rub2,']')==-1)
            {
                i++;
                co+=find_char(rub2,'[');
                strcpy(rub2,strchr(rub2,'['));
                strcpy(rub2,Tabdil2(rub2,1));
            }
            else if(find_char(rub2,']')!=-1 && find_char(rub2,'[')==-1)
            {
                i--;
                co+=find_char(rub2,']');
                strcpy(rub2,strchr(rub2,']'));
                strcpy(rub2,Tabdil2(rub2,1));
            }
        }
        for(i=0;i<=co;i++)
            rub4[i]=rub3[i];
        strcat(rub4,"]");
        return rub4;
    }
}
int GetAS(char aray[10000])
{
    if(strchr(aray,'{')!=NULL)
    {
        int i=0;
        strcpy(rub,aray);
        while(strstr(rub,"}, {")!=NULL)
        {
            i++;
            strcpy(rub,strstr(rub,"}, {"));
            strcpy(rub,Tabdil2(rub,4));
        }
        return i+1;
    }
    else
        return 0;
}
char* GetA(char aray[10000],int i)
{
    if(strchr(aray,'{')!=NULL)
    {
        strcpy(rub,aray);
        int j=0;
        strcpy(rub,strchr(rub,'{'));
        strcpy(rub,Tabdil2(rub,1));
        while(j<i)
        {
            j++;
            if(strstr(rub,"}, {")!=NULL)
            {
                strcpy(rub,strstr(rub,"}, {"));
                strcpy(rub,Tabdil2(rub,4));
            }
        }
        i=1;
        int co=0;
        while(i!=0)
        {
            if(find_char(rub,'{')<find_char(rub,'}') && find_char(rub,'{')>0)
            {
                i++;
                co+=find_char(rub,'{');
                if(i!=0)
                    strcpy(rub,strchr(rub,'{'));
            }
            else if(find_char(rub,'}')<find_char(rub,'{') && find_char(rub,'}')>0)
            {
                i--;
                co+=find_char(rub,'}');
                if(i!=0)
                    strcpy(rub,strchr(rub,'}'));
            }
            else if(find_char(rub,'{')>0 && find_char(rub,'}')<=0)
            {
                i++;
                co+=find_char(rub,'{');
                if(i!=0)
                    strcpy(rub,strchr(rub,'{'));
            }
            else if(find_char(rub,'}')>0 && find_char(rub,'{')<=0)
            {
                i--;
                co+=find_char(rub,'}');
                if(i!=0)
                    strcpy(rub,strchr(rub,'}'));
            }
        }
        i=0;
        memset(rub2,0,10000);
        for(i;i<co;i++)
            rub2[i]=rub[i];
        memset(rub3,0,10000);
        strcpy(rub3,"{");
        strcat(rub3,rub2);
        strcat(rub3,"}");
        return rub3;
    }
    else
        return "";
}
char* GetAM(char aray[10000],int i)
{
    strcpy(rub,aray);
    int j=0;
    strcpy(rub,strchr(rub,'"'));
    strcpy(rub,Tabdil2(rub,1));
    while(j<i)
    {
        j++;
        if(strstr(rub,"\", \"")!=NULL)
        {
            strcpy(rub,strstr(rub,"\", \""));
            strcpy(rub,Tabdil2(rub,4));
        }
    }
    memset(rub3,0,10000);
    rub3[0]=rub[0];
    for(i=1;i<find_char(rub,'"');i++)
        rub3[i]=rub[i];
    memset(rub4,0,10000);
    strcpy(rub4,"\"");
    strcat(rub4,rub3);
    strcat(rub4,"\"");
    return rub4;
}
int GetASM(char aray[10000])
{
    if(strlen(aray)==2)
        return 0;
    else{
        int i=0;
        strcpy(rub,aray);
        while(strstr(rub,"\", \"")!=NULL)
        {
            i++;
            strcpy(rub,strstr(rub,"\", \""));
            strcpy(rub,Tabdil2(rub,4));
        }
        return i+1;
    }
}
int DelIA(char aray[],int n)
{
    int i,co=0;
    memset(rub,0,10000);memset(rub2,0,10000);
    for(i=0;i<n;i++)
        co+=strlen(GetA(aray,i));
    co+=n*2;
    co+=1;
    strncpy(rub,aray,co);
    strcpy(rub2,aray);
    strcpy(rub2,Tabdil2(rub2,co));
    strcpy(rub2,Tabdil2(rub2,2+strlen(GetA(aray,n))));
    strcat(rub,rub2);
    strcpy(aray,rub);
}
int DelIAM(char aray[],int n)
{
    strcpy(rub5,aray);
    int i,co=0;
    memset(rub,0,10000);memset(rub2,0,10000);
    for(i=0;i<n;i++)
        co+=strlen(GetAM(rub5,i));
    co+=n*2;
    co+=1;
    strncpy(rub,rub5,co);
    rub[co]=NULL;
    strcpy(rub2,rub5);
    strcpy(rub2,Tabdil2(rub2,co));
    strcpy(rub6,rub);
    if(strlen(rub2)==strlen(GetAM(rub5,n))+1)
    {
        strcpy(rub2,Tabdil2(rub2,strlen(GetAM(rub5,n))));
        strcat(rub6,rub2);
        rub6[strlen(rub6)-3]=rub6[strlen(rub6)-2];
        rub6[strlen(rub6)-2]=rub6[strlen(rub6)-1];
        rub6[strlen(rub6)-1]=NULL;
        rub6[strlen(rub6)-2]=rub6[strlen(rub6)-1];
        rub6[strlen(rub6)-1]=NULL;
    }
    else
    {
        strcpy(rub2,Tabdil2(rub2,2+strlen(GetAM(rub5,n))));
        strcat(rub6,rub2);
    }
    strcpy(aray,rub6);
}
int EX(char* str)
{
    int i;
    char s[10000];
    strcpy(s,str);
    str[strlen(s)-1]=NULL;
    for(i=0;i<strlen(s);i++)
        s[i]=s[i+1];
    if(strchr(s,'"')!=NULL)
        s[strlen(s)-1]=NULL;
    for(i=0;i<usCount;i++){
        printf("%s\n",user_online[i]);
        if(strcmp(s,user_online[i])==0)
            return 1;
    }
    return 0;
}
int Poi(char* str,char* wrd)
{
    char s1[100],s2[100];memset(s1,0,100);memset(s2,0,100);
    char w[10000];strcpy(w,str);
    Tabdil2(w,1);
    w[strlen(w)-1]=' ';
    while(find_char(w,' ')!=-1)
    {
        if(strncmp(wrd,w,find_char(w,' '))==0)
            return 1;
        Tabdil2(w,find_char(w,' ')+1);
    }
    return 0;
}
//kind 6
int find_char(char s[10000],char ch)
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]==ch)
            return i;
    }
    return -1;
}
int Tabdil(int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<strlen(order);j++)
            order[j]=order[j+1];
}
char* Tabdil2(char ord[10000] ,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<strlen(ord);j++)
            ord[j]=ord[j+1];
    return ord;
}
