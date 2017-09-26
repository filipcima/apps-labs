// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LEDs
//
// **************************************************************************

#include \"mbed.h\"

int main()
{
    // LEDs on K64F-KIT - instances of class DigitalOut
    DigitalOut LED_BLUE(PTB2);
    
    // Button on K64F-KIT - instance of class DigitalIn
    DigitalIn btn1( PTC9 );
    DigitalIn btn2( PTC10 );
    double jas = 10;
    while( 1 )
    {
        
        for (int i = 0; i < 20; i++) {
            if (i < 20*jas/100) {
                LED_BLUE = 1;
            } else {
                LED_BLUE = 0;
            }
        }
        
        if(!btn1) {
            jas += 0.3;
        };
        if(!btn2) {
            jas -= 0.3;
        };
        
        
    
        
    }
}
