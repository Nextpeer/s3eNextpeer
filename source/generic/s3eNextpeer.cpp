/*
Generic implementation of the s3eNextpeer extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "s3eNextpeer_internal.h"
s3eResult s3eNextpeerInit()
{
    //Add any generic initialisation code here
    return s3eNextpeerInit_platform();
}

void s3eNextpeerTerminate()
{
    //Add any generic termination code here
    s3eNextpeerTerminate_platform();
}
