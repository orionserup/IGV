
#include "IGV.hpp"

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, const char** argv){
  
  IGV igv;
  if(argc > 1 && strncmp(argv[1], "--setup", strlen(argv[1])))
    igv.Setup();
    
  else 
    igv.Setup();
    while(1) 
      igv.Run();

}
