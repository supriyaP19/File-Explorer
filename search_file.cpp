#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;
string file_to_be_searched;
struct stat thestat;
struct dirent **d;
int x=0;

static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	
	printf("%s\n",fpath );
	// char new_path[1024];
	// int j=0,count=0,index=0;
	// if(tflag == FTW_F){
	// 	for(int i=strlen(fpath)-1;i>0;i--){

	// 		if(fpath[i]=='/'){
	// 			index=i;
	// 			break;
	// 		}
	// 		else
	// 			count++;

	// 	}
	// 	for(int i=index+1,j=0;i<strlen(fpath);i++){
	// 		new_path[j++]=fpath[i];
	// 	}
	// 	new_path[count]='\0';
	// 	//cout<<"the file path is "<<new_path<<endl;
	// 	if(new_path==file_to_be_searched){
	// 		cout<<"yes it's there "<<fpath;
	// 		//goback.push(path);
	// 		//ls_command(path,0);
	// 	}
	// 	//cout<<" new_path:"<<new_path<<" "<<"dest1:"<<dest1;
	
	//}

	
	
	return 0;
    
}

int main(int argc, char const *argv[])
{
	string x(argv[1]);
	file_to_be_searched = x;

	int flags = 0;
    if (nftw(".", display_info, 20, flags)== -1) {
    	//cout<<"this file doensn't exist"<<endl;
        perror("nftw : ");
       // exit(EXIT_FAILURE);
    
    }
    //cout<<dest1;

    exit(EXIT_SUCCESS);


    return 0;
}
