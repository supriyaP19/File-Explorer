#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <time.h>
#include <pwd.h>
#include <termios.h>
#include <grp.h>
#include <stack>
#include <sys/ioctl.h>
#include <linux/limits.h>
#include "copy_test.h"
#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",x,";",y,"H");
using namespace std;
struct winsize window;
char option;

int pos_of_x=1;
struct stat thestat;
char path1[200];
int x=1;
int y=1;
int new_x=0;

void cursor_and_flag(struct dirent **thefile,char [],int n);
void ls_command(char [],int start);
void command_mode(string);

stack <string> goback;
stack <string> goforward;


int main()
{   char cur[1];
    cur[0]='.'; 
    //printf("\033[H\033[J");
    getchar();
        ls_command(cur,0);
   
    return 0;

}

void ls_command(char path[],int start){
    
    ioctl(STDIN_FILENO, TIOCGWINSZ, &window);
    int n;
    DIR *thedirectory;
    struct dirent **thefile;
    
    //struct passwd *tf; 
    //struct group *gf;
    float mem;
    char buf[512],slash[1];

    n = scandir(path,&thefile,0,alphasort);
    int count = n;
    int end;
    if(n>34){
        end=start+34;
    }
    else
        end=n-1;
    int i;
    if(n!=-1){
        printf("\033[H\033[J");
        for(i=start;i<=end;i++) 
        {   
            
            sprintf(buf, "%s/%s", ".",(*(thefile+i))->d_name);
            stat(buf, &thestat);

            if(thestat.st_mode & S_IWUSR)
                printf("r");
            else
                printf("-");
            if(thestat.st_mode & S_IRUSR)
                printf("w");
            else
                printf("-");
            if(thestat.st_mode & S_IXUSR)
                printf("x");
            else
                printf("-");
             if(thestat.st_mode & S_IRGRP)
                printf("r");
            else
                printf("-");
             if(thestat.st_mode & S_IWGRP)
                printf("w");
            else
                printf("-");
                    
             if(thestat.st_mode & S_IXGRP)
                printf("x");
            else
                printf("-");
             if(thestat.st_mode & S_IROTH)
                printf("r");
            else
                printf("-");
             if(thestat.st_mode & S_IWOTH)
                printf("w");
            else
                printf("-");
             if(thestat.st_mode & S_IXOTH)
                printf("x");
            else
                printf("-");

            printf(" %20s  ", (*(thefile+i))->d_name);
            mem = thestat.st_size/4096;
            printf("%3.2f %s",mem,"MB");
            printf("\t%5ld ", thestat.st_nlink);
            //OWNERSHIP
            //tf = getpwuid(thestat.st_uid);
            // printf("\t%s ", tf->pw_name);

            // //[group]
            // // http://linux.die.net/man/3/getgrgid
            // gf = getgrgid(thestat.st_gid);
            // printf("\t%s ", gf->gr_name);
            //time.h headerfile is for ctime function that converts time format to string.
            printf(" %s", ctime(&thestat.st_mtime));
         
            }
            
            //------------------------------------------------------------imp
            // if(!goback.empty())
            //     cout<<"goback:  "<<goback.top()<<endl;
            // if(!goforward.empty())
            //     cout<<"goforward:  "<<goforward.top()<<endl;
           
            cout<<"current path "<<path;

          
            //cout<<"new_X: "<<new_x;
            cursor_and_flag(thefile,path,n);
    }
    cout<<"no dir: "<<path;
    cursor_and_flag(thefile,path,n);
    
    closedir(thedirectory);
}

void cursor_and_flag(struct dirent **thefile,char path[],int n){
        //cout<<"inside cursor "<<n;
        
        cout<<"\033["<<pos_of_x<<";"<<y<<"H";
        //x=pos_of_x;
        struct termios initial_settings, new_settings;

        
        
        char ch;
        int choice = 0;
        FILE *input;
        FILE *output;
        char arr[1];
        char parent[1];
        char parent1[1];
        arr[0]='/';
        
        input = fopen("/dev/tty", "r");
        output = fopen("/dev/tty", "w");
               
        tcgetattr(fileno(input),&initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ICANON;

        if(tcsetattr(fileno(input), TCSANOW, &new_settings) != 0) {
                fprintf(stderr,"could not set attributes\n");
        }
        int z,len,temp,flag=0;
        string buff = "Normal Mode";
        // buff = buf;
       cout<<"\033["<<37<<";"<<1<<"H"<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\033["<<38<<";"<<1<<"H"<<buff;
        cout<<"\033["<<x<<";"<<y<<"H";
        while(1){
                ch = getchar();

                if(ch==58){
                    command_mode(buff);

                }   
                // else if(ch=='\033'){
                //     new_settings.c_lflag &= ~ECHO;
                //     tcsetattr(fileno(input), TCSANOW, &new_settings);
                //     cout<<"\033["<<37<<";"<<1<<"H"<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                //     cout<<"\033["<<38<<";"<<1<<"H"<<"Normal Mode:";
                //     cout<<"\033["<<x<<";"<<y<<"H";
                // }
                else if(ch == '\033') { 
                        getchar(); 
                        switch(getchar()) { 
                                case 'A':
                                        //up
                                        if(x!=1 || new_x!=0){
                                           
                                            if(new_x<=34){
                                                 if(x!=1){
                                                     x=x-1;
                                                     new_x=new_x-1;
                                                     gotoxy(x,y);
                                                 }
                                                 else{
                                                     new_x-=1;
                                                     gotoxy(x,y);
                                                     ls_command(path,new_x);
                                                 }
                                                
                                            }
                                            
                                            else if(new_x>34){
                                                
                                                if(x>1){
                                                    x=x-1;
                                                    new_x=new_x-1;
                                                    gotoxy(x,y);
                                                }
                                               
                                               if(x==1){
                                                    
                                                    new_x=new_x-1;
                                                    ls_command(path,new_x);
                                               }
                                            }
                                           
                                        }
                                        
                                        break;
                                case 'B':
                                        //down
                                        if(new_x<n-1){
                                            

                                            if(new_x<34){
                                                //cout<<"new_x: "<<new_x;
                                                x=x+1;
                                                new_x=new_x+1;
                                                gotoxy(x,y);
                                                
                                                
                                            }
                                             else if(new_x>=34){
                                                
                                                new_x=new_x+1;
                                                //cout<<"new_x: "<<new_x;
                                                pos_of_x=34;
                                                ls_command(path,new_x-34);
                                            } 
                                        }
                                       break;
                                case 'C':
                                        //right
                                        x=1;
                                        new_x=0;
                                        if(!goforward.empty()){
                                            goback.push(path);
                                            char top[goforward.top().length()+1];
                                            strcpy(top,goforward.top().c_str());
                                            goforward.pop();
                                            pos_of_x=1;
                                            ls_command(top,0);

                                        }
                                        
                                        
                                        break;
                                case 'D':
                                        //left
                                        x=1;
                                        new_x=0;
                                       if(!goback.empty()){
                                           goforward.push(path);
                                           char top[goback.top().length()+1];
                                           strcpy(top,goback.top().c_str());
                                           goback.pop(); 
                                           pos_of_x=1;
                                           ls_command(top,0);
                                       }
                                     
                                       

                        }
                }
               
                else if(ch == '\n'){
                    //cout<<"hiiii";
                    char cwd[256];
                    x=1;
                    int new_new_x;
                    new_new_x=new_x;
                    new_x=0;
                    //new_x=0;
                    //cout<<"after enter: "<<(*(thefile+x-1))->d_name;
                    stat((*(thefile+new_new_x))->d_name, &thestat);
                    if((thestat.st_mode & S_IFMT)==S_IFDIR){
                        if(new_new_x==0){

                            //ls_command(path);       
                        }
                        else if(new_new_x==1){
                            if (getcwd(cwd, sizeof(cwd))==path){
                                ls_command(path,0);
                            }
                            else{


                                goback.push(path);
                           
                                for(int i=strlen(path)-1;i>0;i--){
                                    if(path[i]=='/'){
                                        path[i]='\0';
                                        break;
                                    }     
                                }
                                pos_of_x=1;
                                ls_command(path,0);
                                


                            }
                        }
                        else{
                            if(!goforward.empty()){
                                //empty goforward
                                while(!goforward.empty()){
                                    goforward.pop();
                                }
                            }
                            goback.push(path);
                            strcat(path,arr);
                            strcat(path,((*(thefile+new_new_x))->d_name));
                            //cout<<"path aftr concatenation"<<path;
                            pos_of_x=1;
                            ls_command(path,0);


                        }
                       
                    }
                }


                //return to home directory
                else if(ch=='h' || ch=='H'){
                    goback.push(path);
                    parent[0]='.';
                    parent[1]='\0';
                    pos_of_x=1;
                    ls_command(parent,0);

                }
                //backspace
                else if(ch==127){
                    cout<<"backspace";
                    goback.push(path);
                    for(int i=strlen(path)-1;i>0;i--){
                        if(path[i]=='/'){
                            path[i]='\0';
                            break;
                        }     
                    }
                    pos_of_x=1;
                    ls_command(path,0);

                    

                }
                //command mode
               
                
                   
                
        }

tcsetattr(fileno(input),TCSANOW,&initial_settings);    

}

void command_mode(string buff){

    struct termios initial_settings, new_settings;
    FILE *input;
    FILE *output;
    input = fopen("/dev/tty", "r");
    output = fopen("/dev/tty", "w");
    tcgetattr(fileno(input),&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ICANON;
   // new_settings.c_cc[VMIN] = 1;
    //new_settings.c_cc[VTIME] = 0;
    //new_settings.c_cc[VTIME] = 0;

    tcsetattr(fileno(input), TCSANOW, &new_settings);
    //printf("\033[H\033[J");
    cout<<"\033["<<37<<";"<<1<<"H"<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    // buff[0] = ':';
    // buff[1] = '\0';
   // cout<<"\033["<<38<<";"<<1<<"H"<<flush;
   cout<<"\033["<<38<<";"<<1<<"H"<<"                                                                                                                            ";
    cout<<"\033["<<38<<";"<<0<<"H"<<"Command Mode :";
    gotoxy(38,15);
    //cout<<"\033["<<38<<";"<<14<<"H";
    char buffer[PATH_MAX];
    buffer[0]='\0';

    char ch,nul_char;
    int i=0;
    while(1){
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ICANON;
        tcsetattr(fileno(input), TCSANOW, &new_settings);
        ch=getchar();
        if(ch!=27&& ch!=127 && ch!='\n'){
            cout<<ch;
            buffer[i++]=ch;
            buffer[i]='\0';
            // buffer=buffer+ch;
        }
        //backspace
        if(ch==127){
            // if(i>0){
            //     buffer[i-2]='\0';
            //     cout<<"\033["<<1<<"K";
            //     cout<<"\033["<<38<<";"<<0<<"H"<<"Command Mode :"<<buffer;   
            //     i--;
            // }
            if(i>0){
                cout<<"\b \b";
                buffer[i]='\0';
                i--;
                }
          
            
        }
        //escape
        if(ch==27){
            //cin.clear();
             new_settings.c_cc[VMIN] = 0;
             new_settings.c_cc[VTIME] = 1;
              //new_settings.c_lflag &= ~ECHO;
               tcsetattr(fileno(input), TCSANOW, &new_settings);
             ch=getchar();
             //new_settings.c_lflag &= ~ECHO;
             if(ch==-1){
                new_settings.c_cc[VMIN] = 1;
                new_settings.c_cc[VTIME] = 0;
                new_settings.c_lflag &= ~ECHO;
                tcsetattr(fileno(input), TCSANOW, &new_settings);
                cout<<"\033["<<1<<";"<<1<<"H";
                //cin.clear();
                //delete[] buffer;
                return;
             }
             else{
                new_settings.c_cc[VMIN] = 1;
                new_settings.c_cc[VTIME] = 0;
                new_settings.c_lflag &= ~ECHO;
                ch=getchar();

               tcsetattr(fileno(input), TCSANOW, &new_settings);
               continue;
             }
             
           
        }
         if(ch==10){
            //cout<<"\033["<<38<<";"<<i<<"H";
           // cout<<buffer;
            std::vector<string>files;
            char file1[PATH_MAX];
            int i=0,j=0;
            do{
                
                if(buffer[i]!=' ' && buffer[i]!='\\'){
                    file1[j]=buffer[i];
                    cout<<"file1:"<<file1[j]<<" buffer:"<<buffer[i]<<endl;
                    j++;
                    i++;
                }
                else if(buffer[i]=='\\' && buffer[i+1]==' '){
                    i++;
                    file1[j]=buffer[i];
                    cout<<"file1:"<<file1[j]<<" buffer: "<<buffer[i]<<endl;
                    i++;    
                    j++;
                    
                }
                else if(buffer[i]==' '){
                    file1[j]='\0';
                    files.push_back(file1);
                    cout<<" file1: "<<file1;
                    cout<<" files current: "<<files.back();
                    j=0;
                    i++;
                }
                
            }while(buffer[i]!='\0');

            file1[j]='\0';
            files.push_back(file1);
            //string case;
            cout<<" source: "<<files[1]<<"destination: "<<files[2];
            if(files[0]=="copy")
                option ='c';
            else if(files[0]=="move")
                option ='m';

            switch(option){
                case 'c' : // printf("=======inside copy========");
                            copy_test(files);
                            break;
                case 'm' : move(files);
                           break;

            }

            }
           
            
            
        }
       

     

    }
       
    

    




// void goto_location(char location[]){
//     char loc[];
//     if(location=='/'){
//         goforward.push(path);
//         loc[0]='.';
//         loc[1]='\0';
//         ls_command(loc);
//     }
//     else{
//         goback.push(path);
//         ls_command(location);
//     }

// }

// void search(){

// }