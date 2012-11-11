#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <sstream>

using namespace std;

int main() {

    ifstream colorKey, mapData;
    ofstream combine;

    string temp, temp1;
    string bname = "<name>";
    string ename = "</name>";
    string bstyle = "<styleUrl>";
    string estyle = "</styleUrl>";
    string searchName;
    int zip;
    string zipstr, hexColor;
    int colorCode;
    bool nameFound;

    mapData.open("zipcodes.kml");
    combine.open("combine.kml");

    int howMany = 0;
    int count2 = 0;

    while(mapData) {
       getline(mapData, temp);

       if(temp.find(bstyle) != string::npos) {
           //remove all styles
           combine << " " << endl;
       } else if(temp.find(bname) == string::npos) {
           //Line by line search for <name>
           //If not found write line as is
           //This will be the most common case.
           combine << temp << endl;
       } else {
           //If <name> is found, check it's value against the list

           colorKey.open("examplezipdata.txt");

           while(colorKey) {
               nameFound = false;
               colorKey >> zip >> colorCode;

               stringstream out;
               out << setw(5) << setfill('0') << zip;
               zipstr = out.str();

               searchName = bname + zipstr + ename;

               if(temp.find(searchName) != string::npos) {
                   nameFound = true;
                   break; //if found get out of loop
               }

           }

           colorKey.close();

           if(nameFound) {
               //if name is on list add name line and new style.
               //style based on colorCode.
               //this will be the more common case.

               stringstream out2;
               colorCode = 210 - colorCode;
               out2 << std::hex << colorCode;
               hexColor = out2.str();

               //cout << std::hex << colorCode << endl;

               string newStyle = bstyle + "#stylemap_" + hexColor + estyle;

               combine << searchName << endl << newStyle << endl;





           } else {
               //if name not on list, just write line to file.
                 combine << temp << endl;
           }
       }
    }

    //colorKey.close();
    mapData.close();
    combine.close();

    return 0;
}
