#include "in.h"

int main(int argc, char const *argv[])
{
	
	// extern char** environ;

	// int count = 0;

	// char *hi = {'a','b','c'};
	// environ[19]=hi;

	// while(environ[count]!=NULL){
	// 	std::cout<<count<<":";
	// 	printf("%s\n", environ[count]);
	// 	count++;
	// }


	std::cout<<getenv("USER");

	return 0;
}