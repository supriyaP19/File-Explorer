#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <stdint.h>
#include <sys/stat.h>
//#include "copy_test.h"
using namespace std;
string dest1;
string dest;
struct stat thestat1;
void copyfile(string fstrpath,string dest2);
vector<string> files;

static int copy_dir(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	
	string fstrpath(fpath);
    //cout<<"x "<<x;
	if(tflag == FTW_D){
		//cout<<"tflag "<<tflag;
		dest1 = dest1+"/"+fstrpath;
		cout<<"inside copy_dir after concatenation : "<<dest1<<endl;
		const int dir_err = mkdir(dest1.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		
		cout<<" dir_err "<<dir_err;
		dest1=dest;

	}
	else if(tflag == FTW_F){
		copyfile(fstrpath,dest);
	}
	
	return 0;
    
}

int main()
{	
	//cout<<"heyyyyyyyyyyyyyyyy";
	files.push_back("copy");
	files.push_back("d11");
	files.push_back("dest_folder");
	dest1 = files[files.size()-1];
	dest=dest1;
	int flags = 0;
	cout<<"destination file "<<dest1<<endl;
	for(int i=1;i<files.size()-1;i++){
		cout<<"inside copy function copying source file:"<<files[i];
		if (nftw(files[i].c_str(), copy_dir, 20, flags)== -1) {
	        perror("nftw error");
	        //exit(EXIT_FAILURE);
    	}

	}
	return 0;
}

void copyfile(string fstrpath,string dest2){
	dest2 = dest2+ "/" + fstrpath;
	stat(fstrpath.c_str(), &thestat1);
    chmod(dest2.c_str(),thestat1.st_mode);
	std::ifstream  src(fstrpath, std::ios::binary);
    std::ofstream  dst(dest2,   std::ios::binary);
	dst << src.rdbuf();	
}
