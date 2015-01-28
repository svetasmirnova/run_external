#include "run_external_udf.h"

long long run_external(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error)
{
	char *command = new char[args->lengths[0]+1];
	command = args->args[0];
	command[args->lengths[0]] = '\0';
	int result = system(command);
	if (0 != result)
		return false;
	else
		return true;
}

my_bool run_external_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
	if (args->arg_count < 1) {
		strcpy(message, "You must specify at least one argument");
		return 1;
	}

	for (unsigned int i = 0; i < args->arg_count; i ++) {
		if (args->arg_type[0] != STRING_RESULT) {
			strcpy(message, "RUN_EXTERNAL accepts only string arguments");
			return 1;
		}
	}

	if (!(initid->ptr = (char*)malloc(MAXRES))) {
		strcpy(message,"Couldn't allocate memory for result buffer");
		return 1;
	}
	memset(initid->ptr, '\0', MAXRES);

	initid->maybe_null = 1;
	initid->max_length = 1;
	initid->const_item = 0;
	
	return 0;
}

void run_external_deinit(UDF_INIT *initid)
{
	if (initid->ptr)
		free(initid->ptr);
}


