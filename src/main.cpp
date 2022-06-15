//#include "Config.h"
#include "akt.hpp"
#include "nameFileProcessor.hpp"
#include <iostream>
#include <ncurses.h>

using namespace std;

void showScreen()
{
   initscr();
   const auto mainStartRow=1;
   const auto mainStartCol=1;
   const auto mainRows=20;
   const auto mainCols=120;
   WINDOW *main = newwin(mainRows, mainCols, mainStartRow, mainStartCol);
   box(main, 0, 0);

   const auto transStartRow=mainStartRow+mainRows;
   const auto transStartCol=mainStartCol;
   const auto transRows=30;
   const auto transCols=mainCols/2;
   WINDOW *trans = newwin(transRows, transCols, transStartRow, transStartCol);
   box(trans, 0, 0);

   const auto divStartRow=transStartRow;
   const auto divStartCol=transStartCol+transCols;
   const auto divRows=transRows;
   const auto divCols=transCols;
   WINDOW *div = newwin(divRows, divCols, divStartRow, divStartCol);
   box(div, 0, 0);

   const auto statusStartRow=transStartRow+transRows;
   const auto statusStartCol=mainStartCol;
   const auto statusRows=3;
   const auto statusCols=mainCols;
   WINDOW *status = newwin(statusRows, statusCols, statusStartRow, statusStartCol);
   box(status, 0, 0);

   refresh();
   mvwprintw(status, 1, 1, "abc def ghi");
   wrefresh(main);
   wrefresh(status);
   wrefresh(trans);
   wrefresh(div);
   getch();
   endwin();
}

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

   showScreen();
   return 0;
}
