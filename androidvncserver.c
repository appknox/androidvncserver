#include <rfb/rfb.h>
#include <stdint.h>
#include "flinger.h"
#include "common.h"

int main(int argc,char** argv)
{

    initFlinger();
    uint8_t *b;
    char *data;
    data = (char *)malloc(screenformat.size);
    b = readBufferFlinger();
    memcpy(data, b, screenformat.size);
    rfbScreenInfoPtr server=rfbGetScreen(&argc,argv,screenformat.width,screenformat.height,8,3,screenformat.bytesPerPixel);
    if(!server)
        return 0;
    server->frameBuffer=data;
    server->paddedWidthInBytes = screenformat.rowStride*screenformat.bytesPerPixel;
    rfbInitServer(server);
    rfbRunEventLoop(server,-1,FALSE);
    return(0);
}
