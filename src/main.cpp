//#include "Config.h"
#include "akt.hpp"
#include "nameFileProcessor.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      cout << "Usage: divp <path/to/div>" << endl;
      return 1;
   }
   string path{argv[1]};
   // cout << "dv: Version " << dv_VERSION_MAJOR << "." << dv_VERSION_MINOR
   //      << endl;
   const auto namesFile = path + "names.txt";
   const auto nfp = NameFileProcessor(namesFile);
   nfp.print();

   const auto aktFile = path + "akt.txt";
   const auto akt = AktFileProcessor(aktFile);
   akt.print();

   return 0;
}
