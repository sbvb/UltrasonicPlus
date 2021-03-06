/*
 * Ultrasonic.h - Library for HC-SR04 Ultrasonic Sensing Module.
 *
 * With ideas from:
 *   Created by ITead studio. Alex, Apr 20, 2010.
 *   iteadstudio.com
 *
 * SVN Keywords
 * ----------------------------------
 * $Author: cnobile $
 * $Date: 2011-12-07 21:49:14 -0500 (Wed, 07 Dec 2011) $
 * $Revision: 38 $
 * ----------------------------------
 *
 * Thank you to Rowan Simms for pointing out the change in header name with
 * Arduino version 1.0 and up.
 *
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#if defined(ARDUINO) && ARDUINO >= 100
 #include "Arduino.h"
 #else
 //#include "WProgram.h"
//#include "Arduino.h"
 #endif
// Undefine COMPILE_STD_DEV if you don't want Standard Deviation.
//#define COMPILE_STD_DEV

typedef struct bufferCtl {
    float *pBegin;
    float *pIndex;
    size_t length;
    bool filled;
} BufCtl;

class Ultrasonic {
public:
    long _timing1;
    Ultrasonic(int tp, int ep);
    long timing();
    float convert(int metric); /*{
    // microsec / 29 / 2;
    if(metric) return microsec / _cmDivisor / 2.0;  // CM
    // microsec / 74 / 2;
    else return microsec / _inDivisor / 2.0;  // IN
    }*/
    void setDivisor(float value, int metric);
    static const int IN = 0;
    static const int CM = 1;

#ifdef COMPILE_STD_DEV
    bool sampleCreate(size_t size, ...);
    void sampleClear();
    float unbiasedStdDev(float value, size_t bufNum);
#endif // COMPILE_STD_DEV

private:
    int _trigPin;
    int _echoPin;
    float _cmDivisor;
    float _inDivisor;
   
    

#ifdef COMPILE_STD_DEV
    size_t _numBufs;
    BufCtl *_pBuffers;
    void _sampleUpdate(BufCtl *buf, float msec);
    void _freeBuffers();
#endif // COMPILE_STD_DEV
};

#endif // ULTRASONIC_H
