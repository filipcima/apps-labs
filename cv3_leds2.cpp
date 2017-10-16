#include "mbed.h"
 
Serial pc( USBTX, USBRX );
 
int main()
{
    pc.baud( 115200 );
 
    // BTNS
    DigitalIn Btn1(PTC9);
    DigitalIn Btn2(PTC10);
    DigitalIn Btn3(PTC11);
    DigitalIn Btn4(PTC12);
 
    // LEDS
    DigitalOut RowLed0(PTC0);
    DigitalOut RowLed1(PTC1);
    DigitalOut RowLed2(PTC2);
    DigitalOut RowLed3(PTC3);
    DigitalOut RowLed4(PTC4);
    DigitalOut RowLed5(PTC5);
    DigitalOut RowLed6(PTC7);
    DigitalOut RowLed7(PTC8);

    DigitalOut ledArray[8] = {RowLed0, RowLed1, RowLed2, RowLed3, RowLed4, RowLed5, RowLed6, RowLed7};
    
    double ledBrightness[8] = {100,100,100,100,100,100,100,100};
    
    int actualPosition = 0;

    for(int i = 0; i < 8; i++) {
        ledArray[i] = 1;
    }
    while( 1 )
    { 
        for(int i = 0; i < 20; i++) {
            for (int j = 0; j < 8; j++){
                if(i < 20 * ledBrightness[j] / 100.0) {
                    ledArray[j] = 1;
                } else {
                    ledArray[j] = 0;
                }
            }
            wait_ms(1);
        }
        
 
        int counter1 = 0;
        int counter2 = 0;
 
        while(!Btn2) {
            if(counter1 == 0) {
                pc.printf("Actual val=%d\n\r", actualPosition);
                if(actualPosition < 7) {
                    actualPosition++;
                }
            }
            counter1++;

 
        }

        while(!Btn1) {
            if(counter2 == 0) {
                pc.printf("Actual val=%d\n\r", actualPosition);
                if(actualPosition > 0) {
                    actualPosition--;
                }
            }
            counter2++;
        }
 
 
        if(!Btn3) { //uber jas
            if(ledBrightness[actualPosition] >= 0) {
                ledBrightness[actualPosition] -= 0.2;
            }
        }
        if(!Btn4) { // pridej jas
            if(ledBrightness[actualPosition] < 100) {
                ledBrightness[actualPosition] += 0.2;
            }
        }
 
    }
}