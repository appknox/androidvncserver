/*
droid vnc server - Android VNC server
Copyright (C) 2011 Jose Pereira <onaips@gmail.com>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <dlfcn.h>

#include "flinger.h"
#include "common.h"

void *flinger_lib = NULL;

close_fn_type close_flinger = NULL;
readfb_fn_type readfb_flinger = NULL;
checkfb_fn_type checkfb_flinger = NULL;
getscreenformat_fn_type getscreenformat_flinger = NULL;

int initFlinger(void)
{
    L("--Loading flinger native lib--\n");
    int i,len;
    char lib_name[64];
    sprintf(lib_name, DVNC_LIB_PATH "/libdvnc_flinger_sdk.so");

    // 1. Open lib
    flinger_lib = dlopen(lib_name, RTLD_NOW);
    if (flinger_lib == NULL) {
        L("Couldnt load flinger library %s! Error string: %s\n", lib_name, dlerror());
        return -1;
    }

    // 2. Bind functions
    init_fn_type init_flinger = dlsym(flinger_lib,"init_flinger");
    if (init_flinger == NULL) {
        L("Couldn't load init_flinger! Error string: %s\n", dlerror());
        return -1;
    }

    close_flinger = dlsym(flinger_lib,"close_flinger");
    if (close_flinger == NULL) {
        L("Couldn't load close_flinger! Error string: %s\n", dlerror());
        return -1;
    }

    readfb_flinger = dlsym(flinger_lib,"readfb_flinger");
    if (readfb_flinger == NULL) {
        L("Couldn't load readfb_flinger! Error string: %s\n", dlerror());
        return -1;
    }

    checkfb_flinger = dlsym(flinger_lib,"checkfb_flinger");
    if (checkfb_flinger == NULL) {
        L("Couldn't load checkfb_flinger! Error string: %s\n", dlerror());
        return -1;
    }

    getscreenformat_flinger = dlsym(flinger_lib,"getscreenformat_flinger");
    if (getscreenformat_flinger == NULL) {
        L("Couldn't load get_screenformat! Error string: %s\n", dlerror());
        return -1;
    }

    int ret = init_flinger();
    if (ret == -1) {
         L("flinger method not supported by this device!\n");
         return -1;
    }

    screenformat = getScreenFormatFlinger();
    if (screenformat.width <= 0) {
        L("Error: I have received a bad screen size from flinger.\n");
        return -1;
    }

    if (checkBufferFlinger() == NULL) {
        L("Error: Could not read surfaceflinger buffer!\n");
        return -1;
    }
    return 0;
}

screenFormat getScreenFormatFlinger(void)
{
    screenFormat f;
    if (getscreenformat_flinger)
         f = getscreenformat_flinger();
    return f;
}

void closeFlinger(void)
{
    if (close_flinger)
        close_flinger();
    if (flinger_lib)
        dlclose(flinger_lib);
}

unsigned char *readBufferFlinger(void)
{
    if (readfb_flinger)
        return readfb_flinger();
    return NULL;
}

unsigned char *checkBufferFlinger(void)
{
    if (checkfb_flinger)
        return checkfb_flinger();
    return NULL;
}
