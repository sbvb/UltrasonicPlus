/*
 * Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Sensing Module.
 *
 * With ideas from:
 *   Created by ITead studio. Apr 20, 2010.
 *   iteadstudio.com
 *
 * SVN Keywords
 * ----------------------------------
 * $Author: cnobile $
 * $Date: 2011-10-08 21:07:42 -0400 (Sat, 08 Oct 2011) $
 * $Revision: 35 $
 * ----------------------------------
 *
 * Centimeters Divisor
 * =========== =======
 *  15.875     26.9029
 *  46.355     27.6233
 *  92.075     28.1949
 * 137.795     28.4717
 * 183.515     28.5584
 * 229.235     28.5936
 * 274.955     28.7194
 *
 * Inches      Divisor
 * ======      =======
 *   6.25      68.3333
 *  18.25      70.1633
 *  36.25      71.6152
 *  54.25      72.3182
 *  72.25      72.5384
 *  90.25      72.6277
 * 108.25      72.9473
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Ultrasonic.h"


Ultrasonic::Ultrasonic(int tp, int ep) // This class define the pins and the constants to convert the units
    {
    pinMode(tp, OUTPUT);
    pinMode(ep, INPUT);
    _trigPin = tp;
    _echoPin = ep;
    _cmDivisor = 27.6233;
    _inDivisor = 70.1633;
    }

long Ultrasonic::timing(){
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    double a = pulseIn(_echoPin, HIGH, 4350); // Standard function on Arduino (pulseIn(pin, value, timeout), where timeout is the time used to stop the reading. The chosen value is equivalent to the time that a sound takes to go through 150 cm  )
    return a; 

}

float Ultrasonic::convert(long microsec, int metric){
    // microsec / 29 / 2;
    if(metric){
        double cm;
    cm =  microsec / _cmDivisor / 2.0;  // CM
        return cm;
    }
    // microsec / 74 / 2;
    else return microsec / _inDivisor / 2.0;  // IN
    }

void Ultrasonic::setDivisor(float value, int metric)
    {
    if(metric) _cmDivisor = value;
    else _inDivisor = value;
    }

#ifdef COMPILE_STD_DEV
bool Ultrasonic::sampleCreate(size_t numBufs, ...)
    {
    bool result = false;
    va_list ap;
    _numBufs = numBufs;

    if((_pBuffers = (BufCtl *) calloc(numBufs, sizeof(BufCtl))) != NULL)
        {
        va_start(ap, numBufs);
        BufCtl *buf;
        size_t smpSize;

        for(size_t i = 0; i < _numBufs; i++)
            {
            buf = &_pBuffers[i];
            smpSize = va_arg(ap, size_t);

            if((buf->pBegin = (float *) calloc(smpSize, sizeof(float))) != NULL)
                {
                buf->pIndex = buf->pBegin;
                buf->length = smpSize;
                buf->filled = false;
                result = true;
                }
            else
                {
                result = false;
                break;
                }
            }

        va_end(ap);
        }

    if(!result) _freeBuffers();
    return result;
    }

void Ultrasonic::sampleClear()
    {
    if(_pBuffers)
        {
        BufCtl *buf;

        for(size_t i = 0; i < _numBufs; i++)
            {
            buf = &_pBuffers[i];
            memset(buf, '\0', sizeof(float) * buf->length);
            buf->pIndex = buf->pBegin;
            buf->filled = false;
            }
        }
    }

float Ultrasonic::unbiasedStdDev(float value, size_t bufNum)
    {
    float result = 0.0;

    if(_pBuffers)
        {
        BufCtl *buf = &_pBuffers[bufNum];

        if(buf->length > 1)
            {
            _sampleUpdate(buf, float(value));

            if(buf->filled)
                {
                float sum = 0.0, mean, tmp;

                for(size_t i = 0; i < buf->length; i++)
                    sum += buf->pBegin[i];

                mean = sum / buf->length;
                sum = 0.0;

                for(size_t i = 0; i < buf->length; i++)
                    {
                    tmp = buf->pBegin[i] - mean;
                    sum += (tmp * tmp);
                    }

                result = sqrt(sum / (buf->length - 1));
                //Serial.print(bufNum);
                //Serial.print(" : ");
                //Serial.println(result);
                }
            }
        }

    return result;
    }

void Ultrasonic::_sampleUpdate(BufCtl *buf, float msec)
    {
    if(buf->pIndex >= (buf->pBegin + buf->length))
        {
        buf->pIndex = buf->pBegin;
        buf->filled = true;
        }

    *(buf->pIndex++) = msec;
    }

void Ultrasonic::_freeBuffers()
    {
    if(_pBuffers)
        {
        BufCtl *buf;

        for(size_t i = 0; i < _numBufs; i++)
            {
            buf = &_pBuffers[i];
            free(buf->pBegin);
            }

        free(_pBuffers);
        }
    }
#endif // COMPILE_STD_DEV


class With_Filter : public Ultrasonic {        
public:
    double cmDivisor = 27.6233;
    double inDivisor = 70.1633;
    With_Filter(int tp, int ep): Ultrasonic(tp, ep){
    };
    double filter(double alpha,double(*timing)){
        // filter the result to remove the errors
        // Y[n] = a * X[n] + (1-a) * Y[N-1]
    long previous_reading =(*timing);
    double result_function;
    long y;
    for (int i=0;i>=0;i++) {
        if (i=0){
            y= (*timing);
            previous_reading = result_function;
            return result_function;
        } 
        else {
            y = (alpha*(*timing)) + ((1- alpha)* previous_reading);
            previous_reading = result_function;
            return result_function;
        }
    }    
    }
        
    double after_filter_cm(double(*filter))  {
        // turn the result after the aplication of the filter into cm
        double cm ;
        cm =  (*filter) / cmDivisor ;
        return cm;
        
    };  
    double after_filter_in(double(*filter))  {
        // turn the result after filter into inches
        double in ;
        in = (*filter) / inDivisor ;
        return in;
    }; 
    
   
    bool digital_result(double(*filter))  {
 // turn the result more reliable, depending on the alpha value to be set. If alpha = 1, the filter is off          
      if ((*filter)  >= 4350) return false;
      else return true; // if the enemy is not in the range, return false
      };
};

/*
With_Filter :filter(double alpha, Ultrasonic::timing()){
    // Y[n] = a * X[n] + (1-a) * Y[N-1]
    long previous_reading;
    long result_function;
    for (int i=0;i>=0;i++) {
        if (i=0){
            y= Ultrasonic::timing();
            previous_reading = result_function;
            return result_function;
        } 
        else {
            y= (alpha*Ultrasonic::timing()) + ((1- alpha)*D);
            previous_reading = result_function;
            return result_function;
        }
    }    
        
}
 
 * 
  With_Filter : digital_result(With_Filter:filter(double alpha, Ultrasonic:timing())){
      if (With_Filter:filter()  >= 4350) return false;
      else return true 
  }
 */     
