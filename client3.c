#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <windows.h>

//Global variables

char User[1000],Pass[1000],AuthToken[1000],Extra[1000],Ch_Pass[1000];

//Functions

void EnterProgram();    //--------->
int Menu();             //--------->    Menus
int Chatting_Menu();    //--------->

int User_Pass();        //--------->    Getting username and password

char* PrepareToSend(char order[]);      //-------> This function create the messege that should be sent to server

int Members(char*);        //--------> It is for showing members of channel
int Refresh(char*);         //-------> It is for showing messeges of channel since last seen

int Response(char*);        //--------> This function sends messege to server and receive its answer

int Join_Check(char*);      //--------> This function is used when user wants to join channel and it checks if there is problem or not
int Create_Check(char*);    //--------> This function is used when user wants to create channel and it checks if there is problem or not
int Enter_Check(char*);     //--------> This function is used when user wants to log in and it checks if there is problem or not
int Register_Check(char*);      //--------> This function is used when user wants to register and it checks if there is problem or not
int SU_Check(char*);           //--------> This function is used when user wants to search for a user and it checks if there is problem or not
int SM_Check(char*);            //--------> This function is used when user wants to serach for a word in messeges and it checks if there is problem or not

char* Tabdil(char order[1000] ,int n);  // This function moves on its input([order] here) and return the result (example-----> inputs:"hassan",3, it returns  "san")
int find_char(char s[1000],char ch);    // This function finds the first place which character(ch) exists in the string(s)

char* GetO(char* object,char item[]); // It works like cJSON_GetObjectItem
char* GetA(char aray[],int i);      // It works like cJSON_GetArrayItem used for messeges
int GetAS(char []);                 // It works like cJSON_GetArraySize used for messeges
char* GetAM(char aray[1000],int i);     // It works like cJSON_GetArrayItem  used for members
int GetASM(char []);            // It works like cJSON_GetArraySize used for members

int Daryaft1();         // Makes the Enter menu
int Daryaft2();         // Makes the after Enter menu
int Daryaft3();         // Makes the channel menu
int Daryaft4();         // Makes the public-private choose menu

void delay(int);        // It stops program for some time

//Main

int main()
{
    printf("................................\nHi\nWelcome to my chat application\nHope you Enjoy\n");
    delay(3);

    //Preparing

    memset(AuthToken,0,1000);
    char Mess[1000];
    memset(Mess,0,strlen(Mess));
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);

    //Start

    EnterProgram(Mess);

    //End

    return 0;
}

void EnterProgram(char Mess[])
{
    system("COLOR F0");
    int n;
    memset(Mess,0,strlen(Mess));
    n=Daryaft1();
    if(n==1)
    {
        User_Pass();
        strcpy(Mess,PrepareToSend("Log in"));
        memset(User,0,strlen(User));
        memset(Pass,0,strlen(Pass));
        Response(Mess);
        if(Enter_Check(Mess)==1)
        {
            Menu(Mess);
        }
        else
        {
            EnterProgram(Mess);
        }
    }
    else if(n==2)
    {
        User_Pass();
        strcpy(Mess,PrepareToSend("Register"));
        memset(User,0,strlen(User));
        memset(Pass,0,strlen(Pass));
        Response(Mess);
        Register_Check(Mess);
        EnterProgram(Mess);
    }
    else if(n==4)
        return;
    else if(n==3)
    {
        strcpy(Mess,PrepareToSend("SearchUser"));
        Response(Mess);
        SU_Check(Mess);
        EnterProgram(Mess);
    }
    else{
        printf("Wrong input\n.......................................................\n");
        delay(1);
        EnterProgram(Mess);
    }
}

//Giving Username and Password

int User_Pass()
{
    int i=0,j=0;
    char c='\0';
    printf("................................\nUsername:\n\t");
    while(1)
    {
        scanf("%c",&c);
        if(c=='\n')
            break;
        User[i]=c;
        i++;
    }
    printf("Password:\n\t");
    while(1)
    {
        scanf("%c",&c);
        if(c=='\n')
            break;
        Pass[j]=c;
        j++;
    }
}

//Prepare Strings to Send for Server

char* PrepareToSend(char order[])
{
    char Mess[1000];
    memset(Mess,0,strlen(Mess));
    if(strcmp(order,"Register")==0)
    {
        strcat(Mess,"register ");
        strcat(Mess,User);
        strcat(Mess,", ");
        strcat(Mess,Pass);
    }
    else if(strcmp(order,"Log in")==0)
    {
        strcat(Mess,"login ");
        strcat(Mess,User);
        strcat(Mess,", ");
        strcat(Mess,Pass);
    }
    else if(strcmp(order,"Log out")==0)
    {
        strcat(Mess,"logout ");
        strcat(Mess,AuthToken);
    }
    else if(strcmp(order,"Send Messege")==0)
    {
        int i=0;
        char c;
        char Messege[1000];
        memset(Messege,0,strlen(Messege));
        printf("Enter Messege: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            Messege[i]=c;
            i++;
        }
        char *str = &Messege[i];
        memset(str,0,100);
        strcat(Mess,"send ");
        strcat(Mess,Messege);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
        memset(Messege,0,strlen(Messege));
    }
    else if(strcmp(order,"Create")==0)
    {
        int i=0;
        char c;
        char Channel_Name[1000];
        memset(Channel_Name,0,strlen(Channel_Name)+10);
        printf("Enter channel Name: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            Channel_Name[i]=c;
            i++;
        }
        strcat(Mess,"create channel ");
        strcat(Mess,Channel_Name);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
        memset(Channel_Name,0,strlen(Channel_Name)+10);
    }
    else if(strcmp(order,"Create_P")==0)
    {
        int i=0,j=0;
        char c;
        char Channel_Name[1000],Channel_Pass[1000];
        memset(Channel_Name,0,strlen(Channel_Name)+10);memset(Channel_Pass,0,1000);
        printf("Enter channel Name: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            Channel_Name[i]=c;
            i++;
        }
        printf("Enter channel password: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            Channel_Pass[j]=c;
            j++;
        }
        strcat(Mess,"create channel_p ");
        strcat(Mess,Channel_Name);
        strcat(Mess,", ");
        strcat(Mess,Channel_Pass);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
        memset(Channel_Name,0,strlen(Channel_Name)+10);
    }
    else if(strcmp(order,"Join")==0)
    {
        int i=0;
        char c;
        char Channel_Name[1000];
        memset(Channel_Name,0,strlen(Channel_Name)+10);
        printf("Enter channel Name: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            Channel_Name[i]=c;
            i++;
        }
        strcat(Mess,"join channel ");
        strcat(Mess,Channel_Name);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
        memset(Channel_Name,0,strlen(Channel_Name)+10);
    }
    else if(strcmp(order,"Channel Members")==0)
    {
        strcat(Mess,"channel members ");
        strcat(Mess,AuthToken);
    }
    else if(strcmp(order,"Leave")==0)
    {
        strcat(Mess,"leave ");
        strcat(Mess,AuthToken);
    }
    else if(strcmp(order,"Refresh")==0)
    {
        strcat(Mess,"refresh ");
        strcat(Mess,AuthToken);
    }
    else if(strcmp(order,"Channel Pass")==0)
    {
        strcat(Mess,"channel pass ");
        strcat(Mess,Ch_Pass);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
    }
    else if(strcmp(order,"SearchUser")==0)
    {
        char c,usf[1000]={};
        int i=0;
        strcpy(Mess,"search_U ");
        printf("Enter User: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            usf[i]=c;
            i++;
        }
        strcat(Mess,usf);
    }
    else if(strcmp(order,"SearchMess")==0)
    {
        char c,msgf[1000]={};
        int i=0;
        strcpy(Mess,"search_M ");
        printf("Enter Word: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            msgf[i]=c;
            i++;
        }
        strcat(Mess,msgf);
        strcat(Mess,", ");
        strcat(Mess,AuthToken);
    }
    strcat(Mess,"\n");
    return Mess;
}

int Menu(char Mess[])
{
    system("COLOR B0");
    int n,n2;
    memset(Mess,0,strlen(Mess));
    n=Daryaft2();
    if(n==1)
    {
        strcpy(Mess,PrepareToSend("Join"));
        Response(Mess);
        if(Join_Check(Mess)==1)
        {
            Chatting_Menu(Mess);
        }
        else
        {
            Menu(Mess);
        }
    }
    else if(n==2)
    {
        n2=Daryaft4();
        if(n2==1)
        {
            strcpy(Mess,PrepareToSend("Create"));
            Response(Mess);
            if(Create_Check(Mess)==1)
            {
                Chatting_Menu(Mess);
            }
            else
            {
                Menu(Mess);
            }
        }
        else if(n2==2)
        {
            strcpy(Mess,PrepareToSend("Create_P"));
            Response(Mess);
            if(Create_Check(Mess)==1)
            {
                Chatting_Menu(Mess);
            }
            else
            {
                Menu(Mess);
            }
        }
    }
    else if(n==3)
    {
        strcpy(Mess,PrepareToSend("Log out"));
        Response(Mess);
        EnterProgram(Mess);
    }
    else{
        printf("Wrong input\n..................................................\n");
        delay(1);
        Menu(Mess);
    }
}

int Chatting_Menu(char Mess[])
{
    system("COLOR E0");
    int n;
    memset(Mess,0,strlen(Mess));
    n=Daryaft3();
    if(n==1)
    {
        strcpy(Mess,PrepareToSend("Send Messege"));
        Response(Mess);
        Chatting_Menu(Mess);
    }
    else if(n==2)
    {
        strcpy(Mess,PrepareToSend("Refresh"));
        Response(Mess);
        Refresh(Mess);
        Chatting_Menu(Mess);
    }
    else if(n==3)
    {
        strcpy(Mess,PrepareToSend("Channel Members"));
        Response(Mess);
        Members(Mess);
        Chatting_Menu(Mess);
    }
    else if(n==5)
    {
        strcpy(Mess,PrepareToSend("Leave"));
        Response(Mess);
        Menu(Mess);
    }
    else if(n==4)
    {
        strcpy(Mess,PrepareToSend("SearchMess"));
        Response(Mess);
        SM_Check(Mess);
        Chatting_Menu(Mess);
    }
    else
    {
        printf("Wrong input\n......................................................\n");
        delay(1);
        Chatting_Menu(Mess);
    }
}

//Orders

int Refresh(char *Mess)
{
    char str1[1000],str2[1000];
    memset(str2,0,strlen(str2));memset(str1,0,strlen(str1));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str1,type);
    char sender[1000];  char content_2[1000];
    int i;
    printf("\n");
    for(i = 0 ; i < GetAS(content) ; i++)
    {
        char submess[1000];
        strcpy(submess,GetA(content,i));
        strcpy(sender,GetO(submess,"sender"));
        strcpy(content_2,GetO(submess,"content"));
        strcpy(str1,sender);
        strcpy(str2,content_2);
        printf("%s: %s\n",str1,str2);
    }
    delay(3);
}

int Members(char *Mess)
{
    char str[1000];
    memset(str,0,strlen(str));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str,type);
    int i;
    printf("Members: \n");
    for(i = 0 ; i < GetASM(content) ; i++)
    {
        char submess[1000];
        strcpy(submess,GetAM(content,i));
        strcpy(str,submess);
        printf("- %s\n",str);
    }
    delay(3);
}

//Connection To Server

int Response(char *Mess)
{
    int Socket,i,j;
    Socket=socket(AF_INET,SOCK_STREAM,0);
    //Identifying Server
    struct sockaddr_in serveraddr;

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(12345);

    //Socket and Server

    connect(Socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    send(Socket,Mess,strlen(Mess),0);
    shutdown(Socket,1);
    strcpy(Mess,"");
    recv(Socket,Mess,1000,0);
    shutdown(Mess,0);
    closesocket(Socket);
}

//Checking Functions

int Create_Check(char *Mess)
{
    char str[1000];
    memset(str,0,strlen(str));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str,type);
    if(strcmp(str,"\"Error\"")==0)
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("%s\n",str);
        delay(3);
        return 0;
    }
    else
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("..............................................................................\nYour Channel successfully created\n");
        delay(1);
        return 1;
    }
}

int Join_Check(char *Mess)
{
    char str[1000];
    memset(str,0,strlen(str));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str,type);
    if(strcmp(str,"\"Error\"")==0)
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("%s\n",str);
        delay(3);
        return 0;
    }
    else if(strcmp(str,"\"Private channel\"")==0)
    {
        char c;
        int j=0;
        char pass[1000];
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("\nEnter channel password: ");
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n')
                break;
            pass[j]=c;j++;
        }
        pass[j]=NULL;
        strcpy(Ch_Pass,pass);
        strcpy(Mess,PrepareToSend("Channel Pass"));
        Response(Mess);
        char type2[1000],content2[1000];
        memset(type2,0,1000);memset(content2,0,1000);
        strcpy(type2,GetO(Mess,"type"));
        strcpy(content2,GetO(Mess,"content"));
        strcpy(str,type2);
        if(strcmp(str,"\"Error\"")==0)
        {
            memset(str,0,strlen(str));
            strcpy(str,content2);
            printf("%s\n",str);
            delay(3);
            return 0;
        }
        else
        {
            printf("..................................................................\nSuccessfully enterd channel\n");
            delay(1);
            return 1;
        }
    }
    else
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("......................................................................\nSuccessfully enterd channel\n");
        delay(1);
        return 1;
    }
}

int Enter_Check(char *Mess)
{
    int i;
    char str[1000];
    memset(str,0,strlen(str));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str,type);
    if(strcmp(str,"\"Error\"")==0)
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("%s\n",str);
        delay(3);
        return 0;
    }
    else
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf(".......................................................................\nSuccessfully logged in\n");
        for(i=1;i<strlen(str)-1;i++)
            AuthToken[i-1]=str[i];
        delay(1);
        return 1;
    }
}

int Register_Check(char *Mess)
{
    char str[1000];
    memset(str,0,strlen(str));
    char type[1000],content[1000];
    memset(type,0,1000);memset(content,0,1000);
    strcpy(type,GetO(Mess,"type"));
    strcpy(content,GetO(Mess,"content"));
    strcpy(str,type);
    if(strcmp(str,"\"Error\"")==0)
    {
        memset(str,0,strlen(str));
        strcpy(str,content);
        printf("%s\n",str);
        delay(2);
        return 0;
    }
    else
    {
        printf(".........................................................................\nYour account successfully created\n");
        delay(1);
        return 1;
    }
}

int SM_Check(char* Mess)
{
    int i;
    char str[10000];
    strcpy(str,GetO(Mess,"content"));
    if(GetASM(str)==0)
        printf("Not found.....\n\n");
    else
    {
        printf("Messeges are:\n");
        for(i=0;i<GetASM(str);i++)
            printf("- %s\n",GetAM(str,i));
        printf("\n");
    }
    delay(3);
}
int SU_Check(char* Mess)
{
    printf("%s\n",GetO(Mess,"content"));
    delay(3);
}
//JSON functions

char* GetO(char* object,char item[1000])
{
    int i,j;
    char p[1000],s[1000],s2[1000],s3[1000],s4[1000];
    memset(s2,0,1000);memset(s,0,1000);memset(s4,0,1000);memset(p,0,1000);memset(s3,0,1000);
    strcpy(p,"\"");
    strcat(p,item);
    strcat(p,"\":");
    strcpy(s,strstr(object,p));
    strcpy(s,Tabdil(s,strlen(p)));
    if((find_char(s,'"')<find_char(s,'[') && find_char(s,'"')!=-1) || find_char(s,'[')==-1)
    {
        strcpy(s,strchr(s,'"'));
        s2[0]=s[0];
        for(i=1;s[i]!='"';i++)
            s2[i]=s[i];
        s2[i]=s[i];
        return s2;
    }
    else
    {
        strcpy(s,strchr(s,'['));
        strcpy(s2,s);
        i=1;
        strcpy(s,Tabdil(s,1));
        int co=0;
        while(i!=0)
        {
            if(find_char(s,'[')<find_char(s,']') && find_char(s,'[')!=-1)
            {
                i++;
                co+=find_char(s,'[');
                strcpy(s,strchr(s,'['));
                strcpy(s,Tabdil(s,1));
            }
            else if(find_char(s,']')<find_char(s,'[') && find_char(s,']')!=-1)
            {
                i--;
                co+=find_char(s,']');
                strcpy(s,strchr(s,']'));
                strcpy(s,Tabdil(s,1));
            }
            else if(find_char(s,'[')!=-1 && find_char(s,']')==-1)
            {
                i++;
                co+=find_char(s,'[');
                strcpy(s,strchr(s,'['));
                strcpy(s,Tabdil(s,1));
            }
            else if(find_char(s,']')!=-1 && find_char(s,'[')==-1)
            {
                i--;
                co+=find_char(s,']');
                strcpy(s,strchr(s,']'));
                strcpy(s,Tabdil(s,1));
            }
        }
        for(i=0;i<=co;i++)
            s3[i]=s2[i];
        return s3;
    }
}
int GetAS(char aray[1000])
{
    if(strchr(aray,'{')!=NULL)
    {
        int i=0;
        char s[1000];
        strcpy(s,aray);
        while(strstr(s,"}, {")!=NULL)
        {
            i++;
            strcpy(s,strstr(s,"}, {"));
            strcpy(s,Tabdil(s,4));
        }
        return i+1;
    }
    else
        return 0;
}
char* GetA(char aray[1000],int i)
{
    if(strchr(aray,'{')!=NULL)
    {
        char s[1000];
        strcpy(s,aray);
        int j=0;
        strcpy(s,strchr(s,'{'));
        strcpy(s,Tabdil(s,1));
        while(j<i)
        {
            j++;
            if(strstr(s,"}, {")!=NULL)
            {
                strcpy(s,strstr(s,"}, {"));
                strcpy(s,Tabdil(s,4));
            }
        }
        i=1;
        int co=0;
        while(i!=0)
        {
            if(find_char(s,'{')<find_char(s,'}') && find_char(s,'{')>0)
            {
                i++;
                co+=find_char(s,'{');
                if(i!=0)
                    strcpy(s,strchr(s,'{'));
            }
            else if(find_char(s,'}')<find_char(s,'{') && find_char(s,'}')>0)
            {
                i--;
                co+=find_char(s,'}');
                if(i!=0)
                    strcpy(s,strchr(s,'}'));
            }
            else if(find_char(s,'{')>0 && find_char(s,'}')<=0)
            {
                i++;
                co+=find_char(s,'{');
                if(i!=0)
                    strcpy(s,strchr(s,'{'));
            }
            else if(find_char(s,'}')>0 && find_char(s,'{')<=0)
            {
                i--;
                co+=find_char(s,'}');
                if(i!=0)
                    strcpy(s,strchr(s,'}'));
            }
        }
        i=0;
        char s3[1000];
        memset(s3,0,1000);
        for(i;i<co;i++)
            s3[i]=s[i];
        char s4[1000];
        memset(s4,0,1000);
        strcpy(s4,"{");
        strcat(s4,s3);
        strcat(s4,"}");
        return s4;
    }
    else
        return "";
}
char* GetAM(char aray[1000],int i)
{
    char s[1000];
    strcpy(s,aray);
    int j=0;
    strcpy(s,strchr(s,'"'));
    strcpy(s,Tabdil(s,1));
    while(j<i)
    {
        j++;
        if(strstr(s,"\", \"")!=NULL)
        {
            strcpy(s,strstr(s,"\", \""));
            strcpy(s,Tabdil(s,4));
        }
    }
    char s3[1000];
    memset(s3,0,1000);
    s3[0]=s[0];
    for(i=1;i<find_char(s,'"');i++)
        s3[i]=s[i];
    char s4[1000];
    memset(s4,0,1000);
    strcpy(s4,"\"");
    strcat(s4,s3);
    strcat(s4,"\"");
    return s4;
}
int GetASM(char aray[1000])
{
    if(strlen(aray)==2)
        return 0;
    else{
        int i=0;
        char s[1000];
        strcpy(s,aray);
        while(strstr(s,"\", \"")!=NULL)
        {
            i++;
            strcpy(s,strstr(s,"\", \""));
            strcpy(s,Tabdil(s,4));
        }
        return i+1;
    }
}
int find_char(char s[1000],char ch)
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]==ch)
            return i;
    }
    return -1;
}
char* Tabdil(char order[1000] ,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<strlen(order);j++)
            order[j]=order[j+1];
    return order;
}
int Daryaft1()
{
    system("cls");
    printf("\n\n\t->\t1- Log in\n\n\t  \t2- Sign up\n\n\t  \t3- Search users\n\n\t  \t4- Bye\n");
    char c;
    int k=0,i=1;
    while((c=getch())!=13)
    {
        if(c==72)
        {
            if(i>1)
            {
                system("cls");
                i--;
                if(i==3)
                {
                    printf("\n\n\t  \t1- Log in\n\n\t  \t2- Sign up\n\n\t->\t3- Search users\n\n\t  \t4- Bye\n");
                }
                if(i==2)
                {
                    printf("\n\n\t  \t1- Log in\n\n\t->\t2- Sign up\n\n\t  \t3- Search users\n\n\t  \t4- Bye\n");
                }
                if(i==1)
                {
                    printf("\n\n\t->\t1- Log in\n\n\t  \t2- Sign up\n\n\t  \t3- Search users\n\n\t  \t4- Bye\n");
                }
            }
        }
        if(c==80)
        {
            if(i<4)
            {
                system("cls");
                i++;
                if(i==3)
                {
                    printf("\n\n\t  \t1- Log in\n\n\t  \t2- Sign up\n\n\t->\t3- Search users\n\n\t  \t4- Bye\n");
                }
                if(i==2)
                {
                    printf("\n\n\t  \t1- Log in\n\n\t->\t2- Sign up\n\n\t  \t3- Search users\n\n\t  \t4- Bye\n");
                }
                if(i==4)
                {
                    printf("\n\n\t  \t1- Log in\n\n\t  \t2- Sign up\n\n\t  \t3- Search users\n\n\t->\t4- Bye\n");
                }
            }
        }
    }
    return i;
}
int Daryaft2()
{
    system("cls");
    printf("\n\n\t->\t1- Join channel\n\n\t  \t2- Create channel\n\n\t  \t3- Log out\n");
    char c;
    int k=0,i=1;
    while((c=getch())!=13)
    {
        if(c==72)
        {
            if(i>1)
            {
                system("cls");
                i--;
                if(i==2)
                {
                    printf("\n\n\t  \t1- Join channel\n\n\t->\t2- Create channel\n\n\t  \t3- Log out\n");
                }
                if(i==1)
                {
                    printf("\n\n\t->\t1- Join channel\n\n\t  \t2- Create channel\n\n\t  \t3- Log out\n");
                }
            }
        }
        if(c==80)
        {
            if(i<3)
            {
                system("cls");
                i++;
                if(i==2)
                {
                    printf("\n\n\t  \t1- Join channel\n\n\t->\t2- Create channel\n\n\t  \t3- Log out\n");
                }
                if(i==3)
                {
                    printf("\n\n\t  \t1- Join channel\n\n\t  \t2- Create channel\n\n\t->\t3- Log out\n");
                }
            }
        }
    }
    return i;
}
int Daryaft3()
{
    system("cls");
    printf("\n\n\t->\t1- Send messege\n\n\t  \t2- Refresh\n\n\t  \t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");
    char c;
    int k=0,i=1;
    while((c=getch())!=13)
    {
        if(c==72)
        {
            if(i>1)
            {
                system("cls");
                i--;
                if(i==2)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t->\t2- Refresh\n\n\t  \t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");
                }
                if(i==1)
                {
                    printf("\n\n\t->\t1- Send messege\n\n\t  \t2- Refresh\n\n\t  \t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");                }
                if(i==3)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t  \t2- Refresh\n\n\t->\t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");
                }
                if(i==4)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t  \t2- Refresh\n\n\t  \t3- Channel members\n\n\t->\t4- Search messege\n\n\t  \t5- Leave\n");
                }
            }
        }
        if(c==80)
        {
            if(i<5)
            {
                system("cls");
                i++;
                if(i==2)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t->\t2- Refresh\n\n\t  \t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");
                }
                if(i==5)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t  \t2- Refresh\n\n\t  \t3- Channel members\n\n\t  \t4- Search messege\n\n\t->\t5- Leave\n");                }
                if(i==3)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t  \t2- Refresh\n\n\t->\t3- Channel members\n\n\t  \t4- Search messege\n\n\t  \t5- Leave\n");
                }
                if(i==4)
                {
                    printf("\n\n\t  \t1- Send messege\n\n\t  \t2- Refresh\n\n\t  \t3- Channel members\n\n\t->\t4- Search messege\n\n\t  \t5- Leave\n");
                }
            }
        }
    }
    return i;
}
int Daryaft4()
{
    system("cls");
    printf("\n\n\t->\t1- Public channel\n\n\t  \t2- Private channel\n");
    int i=1;
    char c;
    while((c=getch())!=13)
    {
        if(c==72)
        {
            if(i==2)
            {
                system("cls");
                printf("\n\n\t->\t1- Public channel\n\n\t  \t2- Private channel\n");
            }
            i=1;
        }
        if(c==80)
        {
            if(i==1)
            {
                system("cls");
                printf("\n\n\t  \t1- Public channel\n\n\t->\t2- Private channel\n");
            }
            i=2;
        }
    }
    return i;
}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
