/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   With_Filter.h
 * Author: Ana Clara
 *
 * Created on February 28, 2016, 11:35 PM
 */

#ifndef WITH_FILTER_H
#define WITH_FILTER_H


#include <stddef.h>
#include "Ultrasonic.h"

class With_Filter : public Ultrasonic {
public:
    int _trigPin;
    int _echoPin;
    double cmDivisor = 27.6233;
    double inDivisor = 70.1633;
    double _alpha; 
    With_Filter(int tp, int ep);
    double filter(double alpha,long(*timing));
    double after_filter_cm(double alpha,long(*timing),double(*filter)(double, long));
    double after_filter_in(double alpha,long(*timing),double(*filter)(double, long));
    bool digital_result(double alpha,long(*timing),double(*filter)(double, long));
};


#endif /* WITH_FILTER_H */

