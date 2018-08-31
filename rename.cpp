#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char const *argv[]){
	rename(argv[1],argv[2]);
	return 0;
}