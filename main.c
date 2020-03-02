#include <rfb/rfb.h>

int main(int argc,char** argv)
{
  FILE *pFile;
  char *data;
  data = (char *)malloc(1088*1980*4);
  pFile = fopen("test.dat", "rb");
  fread(data, 1088*1980*4, 1, pFile);
  fclose(pFile);
  rfbScreenInfoPtr server=rfbGetScreen(&argc,argv,1080,1980,8,3,4);
  if(!server)
    return 0;
  server->frameBuffer=data;
  server->paddedWidthInBytes = 1088*4;
  rfbInitServer(server);
  rfbRunEventLoop(server,-1,FALSE);
  return(0);
}
