#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <pwd.h>
#include <termios.h>
#include <grp.h>
#include <stack>
#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",x,";",y,"H");
using namespace std;

int pos_of_x=0;
struct stat thestat;
char path1[200];
int x=0;
int y=0;

void cursor_and_flag(struct dirent **thefile,char [],int n);
void ls_command(char [],int start);
stack <string> goback;
stack <string> goforward;

int main()
{   char cur[1];
    cur[0]='.'; 
    //printf("\033[H\033[J");
    
        ls_command(cur,0);
   
    return 0;

}

void ls_command(char path[],int start){


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
    if(n>36){
        end=start+36;
    }
    else
        end=n;
    if(n!=-1){
        printf("\033[H\033[J");
        for(int i=start;i<end;i++) 
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
            //thefile++;
            }
            //thefile-=count;
            if(!goback.empty())
                cout<<"goback:  "<<goback.top()<<endl;
            if(!goforward.empty())
                cout<<"goforward:  "<<goforward.top()<<endl;
            cout<<"current path "<<path;
            cursor_and_flag(thefile,path,count);
    }
    cout<<"no dir: "<<path;
    cursor_and_flag(thefile,path,count);
    
    closedir(thedirectory);
}

void cursor_and_flag(struct dirent **thefile,char path[],int n){
        //cout<<"inside cursor "<<n;
        //cout<<"x: "<<x;
        cout<<"\033["<<pos_of_x<<";"<<y<<"H";
        x=pos_of_x;
        struct termios initial_settings, new_settings;

        
        
        char ch;
        int choice = 0;
        FILE *input;
        FILE *output;
        char arr[1];
        char parent[1];
        char parent1[1];
        arr[0]='/';
        //cout<<"aftr cumin"<<x;
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
        
        //strcat(path);
        //gquiz.push(path);
        
        //y=x+1;
        //const char cur_path[]="";
        //int times=count;
        //cout<<times;
        while(1){
                ch = getchar();
                if (ch == '\033') { 
                        getchar(); 
                        switch(getchar()) { 
                                case 'A':
                                        //up
                                        if(x!=0){
                                            x=x-1;
                                            gotoxy(x,y);

                                        }
                                        
                                        break;
                                case 'B':
                                        //down
                                        if(x<n){
                                            

                                            if(x<=36 ){

                                                x=x+1;
                                                //cout<<"Downnnnnnnn";
                                                gotoxy(x,y);
                                                cout<<"x: "<<x;
                                                
                                            }
                                            else if(x>36 && x<n){
                                                x=x+1;
                                                cout<<"x: "<<x;
                                                pos_of_x=x;
                                                ls_command(path,x-36);
                                            } 
                                        }
                                       break;
                                case 'C':
                                        //right

                                        if(!goforward.empty()){
                                            goback.push(path);
                                            char top[goforward.top().length()+1];
                                            strcpy(top,goforward.top().c_str());
                                            goforward.pop();
                                            pos_of_x=0;
                                            ls_command(top,0);

                                        }
                                        
                                        
                                        break;
                                case 'D':
                                        //left

                                       if(!goback.empty()){
                                           goforward.push(path);
                                           char top[goback.top().length()+1];
                                           strcpy(top,goback.top().c_str());
                                           goback.pop(); 
                                           pos_of_x=0;
                                           ls_command(top,0);
                                       }
                                     
                                       

                        }
                }
               
                else if(ch == '\n'){
                    //cout<<"hiiii";
                    char cwd[256];
                    //cout<<"after enter: "<<(*(thefile+x-1))->d_name;
                    stat((*(thefile+x-1))->d_name, &thestat);
                    if((thestat.st_mode & S_IFMT)==S_IFDIR){
                        if(x==0 || x==1){

                            //ls_command(path);       
                        }
                        else if(x==2){
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
                                pos_of_x=0;
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
                            strcat(path,((*(thefile+x-1))->d_name));
                            cout<<"path aftr concatenation"<<path;
                            pos_of_x=0;
                            ls_command(path,0);


                        }
                       
                    }
                }



                else if(ch=='h'){
                    goback.push(path);
                    parent[0]='.';
                    ls_command(parent,0);

                }
                else if(ch=8){
                 
                    goback.push(path);
                    for(int i=strlen(path)-1;i>0;i--){
                        if(path[i]=='/'){
                            path[i]='\0';
                            break;
                        }     
                    }
                    ls_command(path,0);

                    

                }
        }
tcsetattr(fileno(input),TCSANOW,&initial_settings);    

}

