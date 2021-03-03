
#include "IGV.hpp"
#include "test.hpp"

using namespace std;
using namespace cv;
using namespace igv;

int main(int argc, const char** argv){
  
  IGV igv;

  if(argc > 1){
    
    if(strncmp(argv[1], "--setup", strlen(argv[1]))) igv.Setup();

    else if(strncmp(argv[1], "--test", strlen(argv[1]))){
      Test test("../test/test.log");
      test.RunAllTests();
    }

    else if( strncmp(argv[1], "-h", 2) || strncmp(argv[1], "--help", 5))
      cout << "Welcome to the IGV Help Menu\n"
           << "'--setup' Runs the Setup Only\n "
           << "'--test' Runs the Tests to specify which one put options after:\n"
           << "\t'cam', 'gps', 'all', 'motor', 'lidar', 'us', 'ld' \n"
           << "\t'od', 'accel', ''(all)";
  
  }

  else{

    igv.Setup();
    igv.Run();

  }
 
}


