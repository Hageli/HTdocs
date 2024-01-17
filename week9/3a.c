#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i;
	char * op;
	double result;

	if ( (op = getenv("OPERATOR")) == NULL) {
		fprintf(stderr, "environment variable OPERATOR not defined\n");
		exit(1);
	}
	printf("Operator: %s\n", op);
	if (argc>1) {
		result=atof(argv[1]);
		for (i=2; i<argc; i++) {
			if (strcmp(op,"add")==0) {
				result += atof(argv[i]);
			}
			if (strcmp(op,"mul")==0) {
				result *= atof(argv[i]);
			}
		}
	} else {
		result=0;
	}

	printf ("result with OPERATOR %s is %f\n", op, result);   

	return 0;
}