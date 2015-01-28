#include <my_global.h>
#include <mysql.h>

#include <string.h>

#ifdef __WIN__
#define WINEXPORT __declspec(dllexport)
#else
#define WINEXPORT
#endif

#define MAXRES 1048576

extern "C" {

WINEXPORT long long run_external(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
WINEXPORT my_bool run_external_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
WINEXPORT void run_external_deinit(UDF_INIT *initid);

}

