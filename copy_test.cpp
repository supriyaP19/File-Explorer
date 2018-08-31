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

static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	string fstrpath(fpath);
	if(tflag == FTW_D){

		
		dest1 = dest1+"/"+fstrpath;
		//cout<<"bc : "<<dest1<<endl;

		const int dir_err = mkdir(dest1.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		dest1=dest;

	}
	else if(tflag == FTW_F){
		copyfile(fstrpath,dest);
	}
	
	return 0;
    
}

int main(int argc, char const *argv[])
{
	dest1 = "dest_folder";
	dest=dest1;
	//dest1(**argv[2]);
	// for(int i=0;i<strlen(argv[2]);i++){
	// 	dest1[i]=argv[2][i];
	// }
	//cout<<"type: "<<typeof(dest1);
	//cout<<"d: "<<dest1;
	// dest = argv[2];
	// for(int i=0;i<argv[2].le)
	int flags = 0;
   // if (argc > 2 && strchr(argv[2], 'd') != NULL)
  //        flags |= FTW_DEPTH;
 //    if (argc > 2 && strchr(argv[2], 'p') != NULL)
//        flags |= FTW_PHYS;

    if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags)== -1) {
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
}
// void copydir(string src,string dest){

// }
