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
#include <sys/ioctl.h>
#include <fcntl.h>
#define gotoxy(x,y) printf("%s%d%s%d%s","\033[",x,";",y,"H");
using namespace std;

void main(){
	int sourcefd,destfd;
	string fname,dfname;
	fname="file1";
	dfname="file2";
	// sourcefd = open(sfname,O_RDONLY);
	// destfd = open(dfname,O_RDONLY);
	// if(sourcefd!=-1){

	// }
	if(sfname[0]!='/' && dfname[0]!='/'){
		cout<<"both r files";
	}
	
	fname="file1";
	dfname="/dir";
	string temp;
	if(sfname[0]!='/' && dfname[0]=='/' ){
		
		temp = dfname + "/" + sfname;
		for(int i=1;i<temp.length();i++){
			temp[i-1]=temp[i];
		}
		cout<<"new dest: "<<temp;
		cout<<"source: "<<sfname;

	}

	fname="/dir1";
	dfname="/dir2";
	
}