#include <didiusJsonIdl.h>
#define N 156
char buf[N];
DataFrame dt(buf,"siser2","01");

void setup(){
  Serial.begin(9600);
}

int Delay = 1000;
void loop(){
  dt.reset();
  dt.Dht(23.0,34.134);
  dt.close();
  Serial.write(buf,dt.len());
  delay(Delay);

  dt.reset();
  dt.addInt("bat",75);
  dt.close();
  Serial.write(buf,dt.len());
  delay(Delay);

  dt.reset();
  dt.Dht(0.0/0.0,45);
  dt.Acc(26.573,23.745,-3.345);
  dt.close();
  Serial.write(buf,dt.len());
  delay(Delay);
}
