
#ifdef UNIMAKE_GET_FLAGS
#error CCFLAGS:-O3:-Wall
#error LDFLAGS:-ldl
#endif

#include <stdio.h>

int main ( int argc, char *argv[] )
{

printf("Hello World\r\n");

return(0);
}
