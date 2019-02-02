#include <iostream>
#include <string>
using namespace std;

int main(){
  string hand;
  int hand2;

  system("start");
  cout << "Do you primarily use your left or right hand?" << endl;
  cin >> hand;

  if(hand == "left" || hand == "Left"){
    // do something
  }
  else if(hand == "right" || hand == "Right"){
    // do something else
  }

  return 0;
}
