#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

#define MAXPATH 256

int list_dir(char * dir, int rec)
{
	DIR * dirp;
	char path[MAXPATH];
	struct dirent * direntp;
	struct stat st;
	
	/* Here you should open the directory indicated by the given path */
	/* check functions opendir */
	
	/* Then you should write a loop that reads the directory and prints the 
	   information about the included files */
	/* check function readdir and stat */

	/* Note the recursion, that is, if rec>0 you should recursively call this 
	   function "list_dir" for subdirectories */

	/* You can use the rec-variable to keep track of the recursion depth
	   and also print it with the file listing */

	/* Make sure you handle directories . and .. correctly 
	   (don't list them recursively, or... What happens??) */

	
	/* closing is already given here, but remember to do it yourself in the future :) */
	if (closedir(dirp) == -1) {
		perror(dir);
		return -1;
	}
	
	return 0;
}

int main(int argc, char * * argv)
{
	int i = 1, rec = 0;
	
	if (argc > 1) {
		if (strcmp(argv[i], "-r") == 0) {
			rec = 1;
			i++;
		}
	}
		
	while (i < argc) {
		if (list_dir(argv[i], rec) == -1) exit(1);
		i++;
	}
		
	return 0;
}
