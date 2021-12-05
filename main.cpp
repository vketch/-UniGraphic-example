/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "stdio.h"
#include "string.h"
#include <string>
#include <vector>

#include "mbed.h"
#include "Arial12x12.h"
#include "Arial24x23.h"

//#include "Terminal6x8.h"
//#include  "hedgehog_240_240_BGR.h"
#include "turtle_240_240_BGR.h"
//#include  "hedgehog_240_240_RGB.h"
//#include "template6_RG5B.h"
//#include "template4_RGB.h"
//#include "template4_RGB.h"
#include "ILI9341V.h"

using namespace std::chrono;

DigitalOut selectSPI(D4, true); // Select SPI iterface on LCD

ILI9341V myLCD(SPI_DMA_, 10000000, D11, D12, D13, D10, D8, D7, "myLCD");

Timer t;

DigitalOut led1(LED1);

unsigned short backgroundcolor = Green;
unsigned short foregroundcolor = Red;


int main() {

  myLCD.set_orientation(0);
  printf("\n\nSystem Core Clock = %.3f MHZ\r\n",
         (float)SystemCoreClock / 1000000);

  myLCD.background(backgroundcolor); 
  myLCD.foreground(foregroundcolor); 
  myLCD.invert(1);

  t.start();

  char orient = 0;
  while (1) {
    myLCD.set_orientation(orient % 4);
    orient++;


    // print text
    myLCD.cls(); // clear the screen
    myLCD.locate(0, 30);
    myLCD.printf("Display ID: %.8X\r\n", myLCD.tftID);
    printf("Display ID: %.8X\r\n", myLCD.tftID);
    ThisThread::sleep_for(2s); 

    myLCD.cls();
    myLCD.set_font((unsigned char *)Terminal6x8, 32, 127,
                   false); // variable width disabled
    myLCD.locate(0, 0);
    myLCD.printf("Display Test\r\nSome text just to see if auto carriage "
                 "return works correctly");
    printf("Display Test\r\nSome text just to see if auto carriage "
                 "return works correctly");                    
    ThisThread::sleep_for(3s); 

    // draw some graphics
    myLCD.cls();
    t.reset();
    myLCD.set_font((unsigned char *)Arial24x23);
    myLCD.locate(10, 10);
    myLCD.printf("Test");

    myLCD.line(0, 0, myLCD.width() - 1, 0, foregroundcolor);
    myLCD.line(0, 0, 0, myLCD.height() - 1, foregroundcolor);
    myLCD.line(0, 0, myLCD.width() - 1, myLCD.height() - 1, foregroundcolor);

    myLCD.rect(10, 30, 50, 40, foregroundcolor);
    myLCD.fillrect(60, 30, 100, 40, foregroundcolor);

    myLCD.circle(150, 32, 30, foregroundcolor);
    myLCD.fillcircle(140, 20, 10, foregroundcolor);

    double s;

    for (unsigned short i = 0; i < myLCD.width(); i++) {
        s = 10 * sin((long double)i / 10);
        myLCD.pixel(i, 40 + (int)s, foregroundcolor);
    }

    unsigned long long time = duration_cast<milliseconds>(t.elapsed_time()).count();
    myLCD.locate(2, 55);
    myLCD.set_font((unsigned char *)Terminal6x8);
    myLCD.printf("plot: %.3f ms", (double)time / 1000);
    printf("plot: %.3f ms\r\n",  (double)time / 1000);
    ThisThread::sleep_for(3s);
     
    //myLCD.Bitmap(0, 0, 240, 240, (unsigned char *)hedgehog_240_240_RGB) ;
    //ThisThread::sleep_for(3s);
    // for (unsigned int i = 0; i < frames; i++) {
    //   myLCD.locate(0, 0);
    //   //     myLCD.move(0, 0, 240, 240, (unsigned char *)turtle_240_240_BGR,
    //   //     i*4);
    //   int res = myLCD.BMP_16(0, 0, "/fs/hedgehog16.bmp");
    //   printf("result of BMP_16 %d \n", res);
    //   ThisThread::sleep_for(5ms);
    // }
    // //    myLCD.Bitmap(0, 0, 240, 240, (unsigned char *)hedgehog_240_240_BGR);

    //myLCD.Bitmap(64, 0, 64, 64, (unsigned char *)template6_Hh_BG5R);
    myLCD.Bitmap(0, 0, 240, 240, (unsigned char *)turtle_240_240_BGR);    
    ThisThread::sleep_for(3s);
    // myLCD.Bitmap(0, 0, 64, 64, (unsigned char *)template4_RGB);
    //    unsigned int frames = 1;
    // myLCD.Bitmap(0, 0, 64, 64, (unsigned char *)template6_BGR);

    // myLCD.Bitmap(0, 0, 48, 34, (unsigned char *)pavement_48x34);
    
    ThisThread::sleep_for(1s);
    led1 = !led1;    

  }

}