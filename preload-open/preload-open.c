/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2007-2014 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

//-------------------------------------------------------------------------
// Function declarations
int open(const char* pathname, int flags, mode_t mode);
int fstat(int fildes, int); // idb

//-------------------------------------------------------------------------
// Data declarations
int (*glibc_open_2433)(const char*, int, mode_t); // weak

// This function was auto-generated by IDA then hand-edited to compile and log output added.
// It opens a file, then ensures that the permissions are set to 1024
// I don't know what 1024 is. But it does what the old preload-open did.
//----- (000005FC) --------------------------------------------------------
int open(const char* pathname, int flags, mode_t mode)
{
    if (strstr(pathname, "C4.log")) // Always ignore BioDB log requests
    {
        return -1;
    }

    FILE* logFile = fopen("logs.0/preload-open.txt", "a");

    if ( !glibc_open_2433 )
    {
        glibc_open_2433 = (int (*)(const char*, int, mode_t))dlsym(RTLD_NEXT, "open");
        char* err = dlerror();
        if ( err )
        {
            fputs(err, (FILE *)2);
            exit(1);
        }
    }

    fprintf(logFile, "Opening file %s with flags %i and mode %u ...", pathname, flags);
    int fd = glibc_open_2433(pathname, flags, mode);

    if ( fd != -1 )
    {
        int newFd = fcntl(fd, 0, 1024);

        if ( newFd >= 0 )
        {
            close(fd);
            fd = newFd;
        }

        fprintf(logFile, " successfully opened file %s.\n", pathname);
    }
    else
    {
        fprintf(logFile, " failed to open file %s because of error %i.\n", pathname, errno);
    }

    fclose(logFile);
    return fd;
}

//----- (00000750) --------------------------------------------------------
int fstat(int fildes, int a2)
{
    return __fxstat(3, fildes, (struct stat *)a2);
}