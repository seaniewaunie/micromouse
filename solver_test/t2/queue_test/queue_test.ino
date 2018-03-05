#include <ArduinoSTL.h>
#include <queue>

using namespace std;

queue<int> test;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  test.push(0);
  test.push(2);
  test.push(4);
  cout << test.front() << endl;
  //cout << "5" << endl;
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
