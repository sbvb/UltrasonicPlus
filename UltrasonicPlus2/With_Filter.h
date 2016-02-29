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

class With_Filter : public Ultrasonic {
public:

    With_Filter(int tp, int ep) : Ultrasonic(tp, ep) {
    };
    double filter(double alpha,double(*timing));
    // double after_filter_cm((double alpha, double(*timing), double(*filter)(double, double)), int CM, float(*convert)(double, int));
    // double after_filter_in();
    bool digital_result(double(*filter));
};


#endif /* WITH_FILTER_H */

