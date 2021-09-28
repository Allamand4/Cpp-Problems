#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Robot {            //create class Robot to store each robot data easily
    public :
    int x, y, facing;  //where they are as x, y, and where they are fdcing as an int

};

Robot robots[25];     //create array of robots assuming maximum of 25 robots (one per square)
bool table[5][5];     // create table array to keep track of robots positions

int getDirection(string com) {




    if (com.find("NORTH") != string::npos) {

        return 0;
        

    }
    if (com.find("EAST") != string::npos) {

        return 1;
        
    }
    if (com.find("SOUTH") != string::npos) {
 
        return 2;
        
    }
    if (com.find("WEST") != string::npos) {

        return 3;
    }
    return 10;
}

void createRobot(int count, string face) {


    robots[count].facing = getDirection(face);

    int x2, y2;

    string x1(1, face[face.find_first_of("01234")]);
    string y1(1, face[face.find_last_of("01234")]);

    stringstream coord(x1);

    coord >> x2;

    stringstream coord1(y1);

    coord1 >> y2;

    table[x2][y2] = true;


    robots[count].x = x2;
    robots[count].y = y2;

    
}



void moveRobot(int robNum, bool tab[][5]) {



    switch (robots[robNum].facing) {

        case 0:

            if (robots[robNum].y < 4 && !(table[robots[robNum].x][robots[robNum].y+1])) {
                tab[robots[robNum].x][robots[robNum].y] = false;
                tab[robots[robNum].x][robots[robNum].y+1] = true;
                cout << "Robot y: " << robots[robNum].y << endl;
                robots[robNum].y++;
                cout << "Robot y: " << robots[robNum].y << endl;
                return;

            } else {
                return;
            }

        case 1:
 
            if (robots[robNum].x < 4 && !(table[robots[robNum].x+1][robots[robNum].y])) {
                tab[robots[robNum].x][robots[robNum].y] = false;
                tab[robots[robNum].x+1][robots[robNum].y] = true;
                robots[robNum].x++;
                return;

            } else {
                return;
            }

        case 2:

            if (robots[robNum].y > 0 && !(table[robots[robNum].x][robots[robNum].y-1])) {
                tab[robots[robNum].x][robots[robNum].y] = false;
                tab[robots[robNum].x][robots[robNum].y-1] = true;
                robots[robNum].y--;
                return;

            } else {
                return;
            }

        case 3:

            if (robots[robNum].x > 0 && !(table[robots[robNum].x-1][robots[robNum].y])) {
                tab[robots[robNum].x][robots[robNum].y] = false;
                tab[robots[robNum].x-1][robots[robNum].y] = true;
                robots[robNum].x--;
                return;

            } else {
                return;
            }
    }
}


 
int main()
{

    string command;
    bool robotPresent = false;
    int currentRob = 0, counter = 0;

    while (1) {

        cout << "Type command: "; getline(cin, command); cout << endl;
        
        

        if (command.find("PLACE") != string::npos) {

            


            createRobot(counter, command);

            counter++;
            
            
            robotPresent = true;
        }

        if (robotPresent == true) {

            if (command.find("MOVE") != string::npos) {
                moveRobot(currentRob, table);
            }

            if (command.find("REPORT") != string::npos) {
                cout << robots[currentRob].x << ", " << robots[currentRob].y << ". Facing " << robots[currentRob].facing << endl;
            }

            if (command.find("LEFT") != string::npos) {
                if (robots[currentRob].facing >= 1) { 
                        robots[currentRob].facing--;
                } else if (robots[currentRob].facing == 0) {
                    robots[currentRob].facing = 3;
                }
            }

            if (command.find("RIGHT") != string::npos) {
                if (robots[currentRob].facing <= 2) { 
                        robots[currentRob].facing++;
                } else if (robots[currentRob].facing == 3) {
                    robots[currentRob].facing = 0;
                }
            }

            // EXTENSION WORK -- assuming multiple robots can be present on the same grid location
            if (counter > 1) {
                if (command.find("ROBOT") != string::npos) {
                    int robInd;
                    string temp = command.substr(6,string::npos);
                    stringstream temp2(temp);
                    temp2 >> robInd;
                    if (robInd <= counter) {
                        currentRob = (robInd - 1);
                    }
            }
            }

        }


        for (int i = 4; i >= 0; i--) {
            for (int j = 0; j < 5; j++) {
                if (table[j][i]) {
                    for (int k = 0; k < counter; k++) {
                        if (robots[k].y == i && robots[k].x == j) {
                            cout << k + 1 << ' ';
                            
                        }
                        
                            
                        
                    };
                } else {
                    cout << "_ ";
                }

            }
            cout << endl;
        }

    }




    return 1;
}