#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std ;


float convert(long microsec, int metric)
    {
    // microsec / 29 / 2;
    if(metric) return microsec / 10/ 2.0;  // CM
    // microsec / 74 / 2;
    else return microsec /5000 / 2.0;  // IN
    }/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
int main(){
    
    cout<< convert (4000, 0)<< endl;
    cout<< convert (4000,1)<< endl;
    return 0;
}
