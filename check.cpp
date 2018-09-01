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
using namespace std;
string dest1;
string dest;
void copyfile(string,string);
struct stat thestat;
int x=0;

static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	string fstrpath(fpath);
	
	
	
    //cout<<"x "<<x;
	
	if(tflag == FTW_D){
		//cout<<"tflag "<<tflag;
		dest1 = dest1+"/"+fstrpath;
		
		const int dir_err = mkdir(dest1.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		dest1=dest;

	}
	else if(tflag == FTW_F){
		copyfile(fstrpath,dest);
	}
	
	return 0;
    
}

int main(int argc, char const *argv[])
{
	string x(argv[2]);
	dest1 = x;
	dest=dest1;
	
    //cout<<" x "<<x;
	int flags = 0;
   // if (argc > 2 && strchr(argv[2], 'd') != NULL)
  //        flags |= FTW_DEPTH;
 //    if (argc > 2 && strchr(argv[2], 'p') != NULL)
//        flags |= FTW_PHYS;

    if (nftw(argv[1], display_info, 20, flags)== -1) {
        perror("nftw");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

    return 0;
}

void copyfile(string fstrpath,string dest2){
	dest2 = dest2+ "/" + fstrpath;
	
	std::ifstream  src(fstrpath, std::ios::binary);
    std::ofstream  dst(dest2,   std::ios::binary);
	dst << src.rdbuf();	
	stat(fstrpath.c_str(), &thestat);
    chmod(dest2.c_str(),thestat.st_mode);
}
