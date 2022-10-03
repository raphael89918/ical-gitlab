#define USE_USBCON

#include <ros.h>

#include <Arduino.h>

#include "wheel_tokyo_weili/encoder.h"

#include "wheel_tokyo_weili/wheel_planner.h"

ros::NodeHandle nh;
wheel_tokyo_weili::encoder e_msg;
ros::Publisher pub("/encoder", &e_msg);
wheel_tokyo_weili::wheel_planner p_msg
ros::Subscriber sub("/encoder/interrupt", &p_msg);

const int ENCODERS = 4; // the number of encoders
const int ENCA[ENCODERS] = { 2, 9, 11, A1}; // set pin
const int ENCB[ENCODERS] = { 3, 10, 13, A5}; // set pin

void readEncoder0();
void readEncoder1();
void readEncoder2();
void readEncoder3();

void setup() {
    //Serial.begin(57600);
    nh.getHardware()->setBaud(57600);
    nh.initNode();
    nh.advertise(pub);
    nh.subscribe(sub);

    pinMode(ENCA[0],INPUT);
    pinMode(ENCB[0],INPUT);
    pinMode(ENCA[1],INPUT);
    pinMode(ENCB[1],INPUT);
    pinMode(ENCA[2],INPUT);
    pinMode(ENCB[2],INPUT);
    pinMode(ENCA[3],INPUT);
    pinMode(ENCB[3],INPUT);

    attachInterrupt(ENCB[0],readEncoder0,RISING);
    attachInterrupt(ENCB[1],readEncoder1,RISING);
    attachInterrupt(ENCA[2],readEncoder2,RISING);
    attachInterrupt(ENCA[3],readEncoder3,RISING);
}

int interval = 100;
int previousMillis = 0;
int pos[ENCODERS] = {};
volatile int posi[ENCODERS] = {};

void loop() {
    int currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;
        pos[0] = posi[0];//因為電路板是做反的 fl
        pos[1] = posi[1];//因為電路板是做反的 bl
        pos[2] = posi[2];//fr
        pos[3] = posi[3];//br

        for(uint8_t i=0;i<4;i++)
        {
            e_msg.wheel_value[i] = posi[i];
        }

        pub.publish(&msg);
        nh.spinOnce();

      /*  Serial.print(pos[0]);
        Serial.print("\t");
        Serial.print(pos[1]);
        Serial.print("\t");
        Serial.print(pos[2]);
        Serial.print("\t");
        Serial.println(pos[3]);*/
    }
}


void readEncoder0(){
    volatile boolean b = digitalRead(ENCA[0]);
    if(b > 0){
        posi[0]++;
    }
    else{
        posi[0]--;
    }
}
void readEncoder1(){
    volatile boolean b = digitalRead(ENCA[1]);
    if(b > 0){
        posi[1]++;
    }
    else{
        posi[1]--;
    }
}
void readEncoder2(){
    volatile boolean b = digitalRead(ENCB[2]);
    if(b > 0){
        posi[2]++;
    }
    else{
        posi[2]--;
    }
}
void readEncoder3(){
    volatile boolean b = digitalRead(ENCB[3]);
    if(b > 0){
        posi[3]++;
    }
    else{
        posi[3]--;
    }
}
