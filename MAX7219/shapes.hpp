/*

          _____                    _____                                            _____                    _____                    _____                    _____          
         /\    \                  /\    \                 ______                   /\    \                  /\    \                  /\    \                  /\    \         
        /::\____\                /::\    \               |::|   |                 /::\    \                /::\____\                /::\____\                /::\    \        
       /::::|   |               /::::\    \              |::|   |                 \:::\    \              /::::|   |               /:::/    /               /::::\    \       
      /:::::|   |              /::::::\    \             |::|   |                  \:::\    \            /:::::|   |              /:::/    /               /::::::\    \      
     /::::::|   |             /:::/\:::\    \            |::|   |                   \:::\    \          /::::::|   |             /:::/    /               /:::/\:::\    \     
    /:::/|::|   |            /:::/__\:::\    \           |::|   |                    \:::\    \        /:::/|::|   |            /:::/    /               /:::/__\:::\    \    
   /:::/ |::|   |           /::::\   \:::\    \          |::|   |                    /::::\    \      /:::/ |::|   |           /:::/    /                \:::\   \:::\    \   
  /:::/  |::|___|______    /::::::\   \:::\    \         |::|   |           ____    /::::::\    \    /:::/  |::|___|______    /:::/    /      _____    ___\:::\   \:::\    \  
 /:::/   |::::::::\    \  /:::/\:::\   \:::\    \  ______|::|___|___ ____  /\   \  /:::/\:::\    \  /:::/   |::::::::\    \  /:::/____/      /\    \  /\   \:::\   \:::\    \ 
/:::/    |:::::::::\____\/:::/  \:::\   \:::\____\|:::::::::::::::::|    |/::\   \/:::/  \:::\____\/:::/    |:::::::::\____\|:::|    /      /::\____\/::\   \:::\   \:::\____\
\::/    / ~~~~~/:::/    /\::/    \:::\  /:::/    /|:::::::::::::::::|____|\:::\  /:::/    \::/    /\::/    / ~~~~~/:::/    /|:::|____\     /:::/    /\:::\   \:::\   \::/    /
 \/____/      /:::/    /  \/____/ \:::\/:::/    /  ~~~~~~|::|~~~|~~~       \:::\/:::/    / \/____/  \/____/      /:::/    /  \:::\    \   /:::/    /  \:::\   \:::\   \/____/ 
             /:::/    /            \::::::/    /         |::|   |           \::::::/    /                       /:::/    /    \:::\    \ /:::/    /    \:::\   \:::\    \     
            /:::/    /              \::::/    /          |::|   |            \::::/____/                       /:::/    /      \:::\    /:::/    /      \:::\   \:::\____\    
           /:::/    /               /:::/    /           |::|   |             \:::\    \                      /:::/    /        \:::\__/:::/    /        \:::\  /:::/    /    
          /:::/    /               /:::/    /            |::|   |              \:::\    \                    /:::/    /          \::::::::/    /          \:::\/:::/    /     
         /:::/    /               /:::/    /             |::|   |               \:::\    \                  /:::/    /            \::::::/    /            \::::::/    /      
        /:::/    /               /:::/    /              |::|   |                \:::\____\                /:::/    /              \::::/    /              \::::/    /       
        \::/    /                \::/    /               |::|___|                 \::/    /                \::/    /                \::/____/                \::/    /        
         \/____/                  \/____/                 ~~                       \/____/                  \/____/                  ~~                       \/____/         
                                                                                                                                                                              

	Author:		Niek Franciscus Geijtenbeek			
	Libary:		MAXimus V1.O
	File:		   shapes.hpp
	
	Copyright Niek Geijtenbeek 2017.
	Distrubyted under the Boost Software License, Version 1.0.
	(See accompanying file "license.txt" or copy at
			http://www.boost.org/LICENSE_1_0.txt)	
*/

#ifndef SHAPES_HPP
#define SHAPES_HPP

#include "coordinate.hpp"
#include "hwlib.hpp"
#include "display.hpp"
#include "math.hpp"

class shapes {
private:
   display & w;
public:
   shapes( display & w ):
      w( w )
   {}
      
void line( coordinate start, coordinate end ){
   int x = start.x;
   int y = start.y;
   int x2 = end.x;
   int y2 = end.y;
   
      bool yLonger=false;
		int shortLen=y2-y;
		int longLen=x2-x;
		if ( abs( shortLen )>abs( longLen )) {
			int swap=shortLen;
			shortLen=longLen;
			longLen=swap;				
			yLonger=true;
		}
		int decInc;
		if ( longLen==0 ) decInc=0;
		else decInc = ( shortLen << 8 ) / longLen;

		if ( yLonger ) {
			if ( longLen>0 ) {
				longLen+=y;
				for ( int j=0x80+(x<<8);y<=longLen;++y ) {
					w.set( coordinate( j >> 8,y ));	
					j+=decInc;
				}
				return;
			}
			longLen+=y;
			for ( int j=0x80+(x<<8);y>=longLen;--y ) {
				w.set( coordinate( j >> 8,y ));	
				j-=decInc;
			}
			return;	
		}

		if ( longLen>0 ) {
			longLen+=x;
			for ( int j=0x80+( y<<8 );x<=longLen;++x ) {
				w.set( coordinate( x,j >> 8 ));
				j+=decInc;
			}
			return;
		}
		longLen+=x;
		for ( int j=0x80+(y<<8);x>=longLen;--x ) {
			w.set(coordinate( x,j >> 8 ));
			j-=decInc;
		}
}
   
void superKitt( coordinate start, coordinate end, uint8_t delay, uint8_t times ){
   
   coordinate tempStart = start;
   coordinate tempEnd = end;
   
   for( int count = 0; count < times; count++ ) {
   for ( int i = 0; i < ( DISPLAY_WIDTH-1 ); i++ ){
      hwlib::wait_ms( delay );
      w.resetMatrix();
      hwlib::wait_ms( delay );
      line( start, end );
      start.shiftRight( 1 );
      end.shiftRight( 1 );
      w.update();
   }
   for ( int i = ( DISPLAY_WIDTH-1 ); i > 0; i-- ){
      hwlib::wait_ms( delay );
      w.resetMatrix();
      hwlib::wait_ms( delay );
      line( start, end );
      start.shiftLeft( 1 );
      end.shiftLeft( 1 );
      w.update();
   }
 }
 
   w.resetMatrix();
   line( tempStart, tempEnd );
   w.update();
   hwlib::wait_ms( delay );
   w.resetMatrix();
   w.update();
}   

void rectangle( coordinate start, coordinate end ){
   coordinate pointOne = start;
   coordinate pointTwo = coordinate( end.x, start.y );
   coordinate pointThree = end;
   coordinate pointFour = coordinate( start.x, end.y );
   
   line( pointOne, pointTwo );
   line( pointTwo, pointThree );
   line( pointThree, pointFour );
   line( pointFour, pointOne );
   
   w.update();
}

// Basic midpoint algorithm
void circle( coordinate midpoint, int radius ){
		int x0 = midpoint.x;
		int y0 = midpoint.y;
		
		int x = radius;
		int y = 0;
		int error = 0;

		while( x >= y ){
			w.set(coordinate( x0 + x, y0 + y ));
			w.set(coordinate( x0 + y, y0 + x ));
			w.set(coordinate( x0 - y, y0 + x ));
			w.set(coordinate( x0 - x, y0 + y ));
			
			w.set(coordinate( x0 - x, y0 - y ));
			w.set(coordinate( x0 - y, y0 - x ));
			w.set(coordinate( x0 + y, y0 - x ));
			w.set(coordinate( x0 + x, y0 - y ));
			
			++y;
			if ( error <= 0 ){
				error+= 2*y + 1;
			}
			if ( error > 0 ){
				--x;
				error -= 2*x + 1;
			}
		}
      w.update();
	}

void triangle( coordinate start, int base, int height ){
   coordinate pointOne = start;
   coordinate pointTwo = coordinate (( start.x + base-1 ), start.y );
   coordinate pointThree = coordinate (( start.x + (( base-1 ) /2 )), ( start.y+ height-1 ));
   
   line( pointOne, pointTwo );
   line( pointOne, pointThree );
   line( pointTwo, pointThree );
   w.update();
}
};
#endif //SHAPES_HPP 