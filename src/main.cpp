
#include "IGV.hpp"

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, const char** argv){
  
  IGV igv;
  if(argc > 1 && argv[1] == "--setup")
    igv.Setup();
  else 
    igv.Setup();
    igv.Run();

}
