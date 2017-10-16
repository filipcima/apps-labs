// **************************************************************************
//
//               Demo program for labs
//
// Subject:      Computer Architectures and Parallel systems
// Author:       Petr Olivka, petr.olivka@vsb.cz, 08/2016
// Organization: Department of Computer Science, FEECS,
//               VSB-Technical University of Ostrava, CZ
//
// File:         Main program for LCD module
//
// **************************************************************************

#include <string>
#include "mbed.h"

Serial pc( USBTX, USBRX );

#include "lcd_lib.h"

// two dimensional array with fixed size font
extern uint8_t font8x8[ 256 ][ 8 ];

int color(unsigned int r, unsigned int g, unsigned int b) {
    r = r / 255 * 31;
    g = g / 255 * 63;
    b = b / 255 * 31;
    
    return (r<<11)|(g<<5)|(b<<0);
}

void putChar(char ch, unsigned int x, unsigned int y, int color) {
    for(int i = 0; i < 8; i++)
        for(int j = 8; j > 0; j--)
            if(font8x8[ch][i]&(1<<j)) LCD_put_pixel(x+j, y+i, color);
}

void print(char* ch, unsigned int x, unsigned int y, int color) {
    for(int i = 0; i < 8; i++) {
        static unsigned int offX = 0;
        putChar(ch[i], 320-x, y+offX, color);
        offX += 8;
        
    }
}

void circle(unsigned int x0, unsigned int y0, unsigned int radius, int color){
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    
    while (x >= y)
    {
        LCD_put_pixel(x0 + x, y0 + y, color);
        LCD_put_pixel(x0 + y, y0 + x, color);
        LCD_put_pixel(x0 - y, y0 + x, color);
        LCD_put_pixel(x0 - x, y0 + y, color);
        LCD_put_pixel(x0 - x, y0 - y, color);
        LCD_put_pixel(x0 - y, y0 - x, color);
        LCD_put_pixel(x0 + y, y0 - x, color);
        LCD_put_pixel(x0 + x, y0 - y, color);
        
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-radius << 1) + dx;
        }
    }
}

void line(int x1, int y1, int x2, int y2, int color) {
    int dx, dy, p, x, y;
    
    dx=x2-x1;
    dy=y2-y1;
    
    x=x1;
    y=y1;
    
    p=2*dy-dx;
    
    while(x<x2)
    {
        if(p>=0)
        {
            LCD_put_pixel(x, y, color);
            y=y+1;
            p=p+2*dy-2*dx;
        }
        else
        {
            LCD_put_pixel(x, y, color);
            p=p+2*dy;
        }
        x=x+1;
    }
}


int main()
{
    LCD_init();             // LCD initialization
    
    LCD_clear();            // LCD clear screen
    
    unsigned int red = color(0, 255, 0);
    int length = 320;
    int width = 240;
    //       Y  X
    
    putChar('B', 310, 0, red);
    putChar('D', 310, 10, red);
    putChar('C', 310, 20, red);
    
    print("EXEC", 20, 10, red);
    //circle(length/2, width/2, 100, red);
    //line(10,10,50,50,red);
    /*
     int scale = 1;
     for(int i = 0; i < 8; i++)
     for(int j = 0; j < 8*scale; j++)
     if(font8x8[\'A\'][i]&(1<<j/scale)) LCD_put_pixel(i*scale, j, red);
     for(int i = 0; i < 8; i++)
     for(int j = 8; j > 0; j--)
     if(font8x8[\'E\'][i]&(1<<j/scale)) LCD_put_pixel(i*scale, j, red);
     */
    
    // simple animation display four color square using LCD_put_pixel function
    /*
     int limit = 200;
     for ( int ofs = 0; ofs < 20; ofs++ ) // square offset in x and y axis
     for ( int i = 0; i < limit; i++ )
     {
     LCD_put_pixel( ofs + i,     ofs + 0,     color_red );
     LCD_put_pixel( ofs + 0,     ofs + i,     color_green );
     LCD_put_pixel( ofs + i,     ofs + limit, color_blue );
     LCD_put_pixel( ofs + limit, ofs + i,     color_white );
     }
     */
    return 0;
}
