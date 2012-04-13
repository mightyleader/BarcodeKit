//
//  Symbol.h
//  BarcodeKit
//
//  Created by Robert Stearn on 13.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_Symbol_h
#define BarcodeKit_Symbol_h

using namespace std;

class Symbol
{
	public:
		Symbol(); //default constructor
		
	
	
	private:
		int leadingElement;
		int intercharacterGap;
		int symbolType;
		int[] encodedSymbol;
}

//Leading Element (integer)
//Does the symbol start with a bar or a space.
//0 - space
//1 - bar
//
//Intercharacter Gap (integer)
//What’s the dimension of the intercharacter gap as a multiple of X?
//0 - no gap (0X)
//1..n - Gap is 1X...nX wide
//
//Symbol Type (integer?)
//What type of symbol does the encoding represent, data or non-data?
//0 - Data
//1 - Check Character
//2 - Quiet Zone
//3 - Guard Pattern
//
//Data (integer[ ])
//Array of values representing widths of each elements in terms of X.
//1 - 1X
//2 - 2X
//3 - 3X
//4 - 4X





#endif
