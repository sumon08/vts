#include <nuttx/config.h>
#include <nuttx/progmem.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

/****************************************************************************
 * vts_main
 ****************************************************************************/
extern int v_main();
 extern "C"
{

	extern void up_cxxinitialize();
	#ifdef CONFIG_BUILD_KERNEL
	int main(int argc, FAR char *argv[])
	#else
	int vts_main(int argc, char *argv[])
	#endif
	{
		up_cxxinitialize();
		
		v_main();
		return 0;
	}

}
