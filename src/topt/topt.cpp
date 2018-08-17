#include "topt.h"

char* toptarg;

const char* toptstr;

int tgetopt(int argc, char** argv, const char* args) {
	if (!toptstr) {
		toptstr = args;
	}
	else {
		toptstr++;
	}

	if (*toptstr == '\0') {
		return -1;
	}

	for (unsigned int i = 0; i < argc; i++) {
		if (**(argv + i) == '-' && *(*(argv+i)+1)==*toptstr) {
			if (*(toptstr + 1) == ':') {
				toptstr++;
				toptarg = *(argv + i + 1);
			}
			return (int)*(*(argv+i)+1);
		}
	}

	return tgetopt(argc, argv, args);
}