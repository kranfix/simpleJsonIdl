#include "didiusJsonIdl.hpp"
#include <stdlib.h>
#include <Arduino.h>

DataFrame::DataFrame(char * buf, char * type, char * id){
  this->buf = buf;
  this->off = sprintf(buf,"{\"dev\":\"%s/%s\"",type,id);
  this->n = this->off;
}

void DataFrame::reset(){
  this->n = this->off;
}

int DataFrame::len(){
  return this->n;
}

void DataFrame::addInt(char * key, int val){
  char * buf = this->buf + this->n;
  this->n += sprintf(buf,",\"%s\":%d",key,val);
}

void DataFrame::addFloat(char * key, float val){
  char * buf = this->buf + this->n;
  String S = String(val);
  this->n += sprintf(buf,",\"%s\":%s",key,S.c_str());
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
    this->n += sprintf(buf,",\"t\":%s",var.c_str());
    if(!h_nan){
      this->buf[this->n] = ',';
      this->n++;
    }
  }
  
  if(!h_nan){
    var = String(h);
    this->n += sprintf(buf,"\"h\":%s",var.c_str());
  }

  this->buf[this->n] = '}';
  this->n++;
}

void DataFrame::Acc(float x, float y, float z){

}

void DataFrame::close(){
  char * buf = this->buf + this->n;
  this->n += sprintf(buf,"}\n");
  return this->buf;
}