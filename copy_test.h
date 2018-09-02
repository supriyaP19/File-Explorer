#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
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


static int copy_dir(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf);
int copy_test(int argc, char const *argv[]);
void copyfile(string fstrpath,string dest2);