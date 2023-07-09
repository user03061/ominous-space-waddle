#include <iostream> // 입력한 숫자(check)가 x와 y사이의 값인지 확인. 
#include <fstream>
using namespace std;

class msg {
  int x,y,check;

  public:
  int SetNumber(){
    char aa[3];
    while (true) {
    cout << "Input Number(Pos1): " << endl;
    cin >> x;
    cout <<  "Input Number(pos2): " << endl;
    cin >> y;
    cout << "Return Number?(Y/N) : " << endl;
    cin >> aa;
    if(aa == "Y") cout << "Return Number" << endl;
    else if (aa == "N") break;
    else cout << "Please Enter Y or N : " << endl; 
    };
    return x, y;
  };
  
  int CheckNumber(){
    cout << "Input Number(Check Number): " << endl;
    cin >> check;
    return check;
  };

  void Checking(ofstream *os1){
    int Swap;
        if(y > x) {
            y = Swap;
            x = y;
            Swap = x;
        }
    if (x <= check <= y) *os1 << check << " is a value between " << x << " and " << y << endl;
    else *os1 << check << " is not a value between " << x << " and " << y << endl; 
  }

};

int main() {
   ofstream os1;
   os1.open("output1.txt");
  
   msg Msgggg;
   
   Msgggg.SetNumber();
   Msgggg.CheckNumber();
   Msgggg.Checking(&os1);
	
return 0;
}