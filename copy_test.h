#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
using namespace std;

//struct stat thestat;

// static int copy_dir(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf);
void copy_test(vector<string> files);
// void copyfile(string fstrpath,string dest2);