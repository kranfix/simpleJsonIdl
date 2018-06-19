#include "didiusJsonIdl.hpp"
#include <stdlib.h>
#include <Arduino.h>

DataFrame::DataFrame(char * buf, char * type, char * id){
  this->buf = buf;
  off = sprintf(buf,"{\"dev\":\"%s/%s\"",type,id);
  n = off;
}

void DataFrame::reset(){
  n = off;
}

int DataFrame::len(){
  return n;
}

void DataFrame::addInt(char * key, int val){
  n += sprintf(&buf[n],",\"%s\":%d",key,val);
}

void DataFrame::addFloat(char * key, float val){
  volatile String S = String(val);
  n += sprintf(&buf[n],",\"%s\":",key);
  S.toCharArray(&buf[n], S.length());
  n += S.length() - 1;
}

void DataFrame::Dht(float t, float h){
  bool t_nan = isnan(t);
  bool h_nan = isnan(t);

  if(t_nan && h_nan){
    return;
  }

  char * buf = this->buf + this->n;
  this->n += sprintf(buf,",\"dht\":{");
  String var;


  if(!t_nan){
    var = String(t);
    buf = this->buf + this->n;
    this->n += sprintf(buf,"\"t\":%s",var.c_str());
    if(!h_nan){
      this->buf[this->n] = ',';
      this->n++;
    }
  }
  
  if(!h_nan){
    var = String(h);
    buf = this->buf + this->n;
    this->n += sprintf(buf,"\"h\":%s",var.c_str());
  }

  this->buf[this->n] = '}';
  this->n++;
}

void DataFrame::Acc(float x, float y, float z){
  String X = isnan(x)? String("\"NaN\"") : String(x);
  String Y = isnan(y)? String("\"NaN\"") : String(y);
  String Z = isnan(z)? String("\"NaN\"") : String(z);

  n += sprintf(buf+n,",\"acc\":[%s,%s,%s]",X.c_str(),Y.c_str(),Z.c_str());
}

void DataFrame::close(){
  n += sprintf(&buf[n],"}\n");
  return buf;
}
