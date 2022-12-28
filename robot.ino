#include <Cytron_SmartDriveDuo.h>
#include <PS4BT.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
BTD Btd(&Usb);

PS4BT PS4(&Btd,PAIR);
float fb,rl;

#include <usbhub.h>

int tr,tl,br,bl,tb,var=0,rr=38,rm=39,lm=40,ll=41,rrr=42,lll=43;


#define IN1 32 
#define AN1 4 
#define AN2 7
#define IN2 33 
#define IN3 30 
#define AN3 5 
#define AN4 6      
#define IN4 31
Cytron_SmartDriveDuo drive_top(PWM_INDEPENDENT, IN1, IN2, AN1, AN2);
Cytron_SmartDriveDuo drive_bottom(PWM_INDEPENDENT, IN3,IN4,AN3,AN4); 

void setup() {
  pinMode(rr,INPUT);
  pinMode(rm,INPUT);
  pinMode(lm,INPUT);
  pinMode(ll,INPUT);  

   Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1);
    }
  Serial.print(F("\r\nPS4 USB Library Started"));
  

}
void RunForward(){
  drive_top.control(50,50);
  drive_bottom.control(-50,-50);
}
void clockwise(){
  drive_top.control(50,50);
  drive_bottom.control(50,50);
}
void anticlockwise(){
  drive_top.control(-50,-50);
  drive_bottom.control(-50,-50);
}
void Right(){
  drive_top.control(50,25);
  drive_bottom.control(25,50);

}
void Left(){
  drive_top.control(25,50);
  drive_bottom.control(50,25);
}
void TopWheelsRight(){
  drive_top.control(50,-50);
  drive_bottom.control(50,50);
}
void TopWheelsLeft(){
  drive_top.control(-50,50);
  drive_bottom.control(50,50);
}
void BottomWheelsRight(){
  drive_top.control(50,50);
  drive_bottom.control(-50,50);
}
void BottomWheelsLeft(){
  drive_top.control(50,50);
  drive_bottom.control(50,-50);
}
void HardRight(){
   drive_top.control(50,0);
  drive_bottom.control(0,50);

}
void HardLeft(){
   drive_top.control(0,50);
  drive_bottom.control(50,0);
}
void loop() {
  Usb.Task();
  if (PS4.connected()){
  if (PS4.getButtonClick(TRIANGLE)){
       var=1+var;
  }
  if (PS4.getButtonClick(CIRCLE)){
    clockwise();

  }
  if (PS4.getButtonClick(SQUARE)){
    anticlockwise();
  }
  if (var%2==0)
  {
  fb=PS4.getAnalogHat(LeftHatY);
  rl=PS4.getAnalogHat(LeftHatX);
  
    
  
  fb=map(fb,0,255,100,-100);
  rl=map(rl,0,255,100,-100);
   if ((fb<10) && (fb>-10)){
     fb=0;
   }
   if ((rl<10) && (rl>-10)){
     rl=0;
   }
  
  
  if ((fb>=0) && (rl>=0))
  {
  tr=sq(fb)-sq(rl);
  tl=sq(fb)+sq(rl);
  br=sq(fb)+sq(rl);
  bl=sq(fb)-sq(rl);
  }
  else if ((fb<0) && (rl>=0))
  {
  tr=-sq(fb)-sq(rl);
  tl=-sq(fb)+sq(rl);
  br=-sq(fb)+sq(rl);
  bl=-sq(fb)-sq(rl);

  }
  else if ((fb<=0) && (rl<0))
  {
  tr=-sq(fb)+sq(rl);
  tl=-sq(fb)-sq(rl);
  br=-sq(fb)-sq(rl);
  bl=-sq(fb)+sq(rl);

  }
  else if ((fb>0) && (rl<0))
  {
  tr=sq(fb)+sq(rl);
  tl=sq(fb)-sq(rl);
  br=sq(fb)-sq(rl);
  bl=sq(fb)+sq(rl);

  }

  if (tr<0){
    tr=-sqrt(-tr);
  }
  else{
    tr=sqrt(tr);
    
  }
  if (tl<0){
    tl=-sqrt(-tl);
  }
  else{
    tl=sqrt(tl);
    
  }
  if (br<0){
    br=-sqrt(-br);
  }
  else{
    br=sqrt(br);
    
  }
  if (bl<0){
    bl=-sqrt(-bl);
  }
  else{
    bl=sqrt(bl);
  }
  drive_top.control(tl,tr);
  drive_bottom.control(-bl,-br);
  }}
  else
{ 
  if (digitalRead(rr)==0 && digitalRead(rrr)==0){
  fb=25;
  rl=25;
 } 
  else if (digitalRead(rr)==0 && digitalRead(rm)==0){
      fb=25;
      rl=12;
      }
 
     


  
  else if (digitalRead(lm)==0&&digitalRead(ll)==0){
      fb=25;
      rl=-12;
    


  }
  else if(digitalRead(ll)==0&&digitalRead(lll)==0){
      fb=25;
      rl=-25;

  }
   else {
      fb=25;
      rl=0;
   }

  
  if ((fb>=0) && (rl>=0))
  {
  tr=sq(fb)-sq(rl);
  tl=sq(fb)+sq(rl);
  br=sq(fb)+sq(rl);
  bl=sq(fb)-sq(rl);
  }
  else if ((fb<0) && (rl>=0))
  {
  tr=-sq(fb)-sq(rl);
  tl=-sq(fb)+sq(rl);
  br=-sq(fb)+sq(rl);
  bl=-sq(fb)-sq(rl);

  }
  else if ((fb<=0) && (rl<0))
  {
  tr=-sq(fb)+sq(rl);
  tl=-sq(fb)-sq(rl);
  br=-sq(fb)-sq(rl);
  bl=-sq(fb)+sq(rl);

  }
  else if ((fb>0) && (rl<0))
  {
  tr=sq(fb)+sq(rl);
  tl=sq(fb)-sq(rl);
  br=sq(fb)-sq(rl);
  bl=sq(fb)+sq(rl);

  }

  if (tr<0){
    tr=-sqrt(-tr);
  }
  else{
    tr=sqrt(tr);
    
  }
  if (tl<0){
    tl=-sqrt(-tl);
  }
  else{
    tl=sqrt(tl);
    
  }
  if (br<0){
    br=-sqrt(-br);
  }
  else{
    br=sqrt(br);
    
  }
  if (bl<0){
    bl=-sqrt(-bl);
  }
  else{
    bl=sqrt(bl);
  }
  drive_top.control(tl,tr);
  drive_bottom.control(-bl,-br);
  }

  
}
