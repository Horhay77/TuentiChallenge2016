#include <iostream>

using namespace std;

int main(){
  int cases;
  int diners;
  int tables;
  cin >> cases;
  for(int i = 0; i < cases; i++){
    cin >> diners;
    if(diners <= 0) tables = 0;
    else if(diners <5) tables = 1;
    else tables = (diners-1)/2;
    cout << "Case #"<< i+1<< ": "<< tables << endl;
  }
  return 0;
}
