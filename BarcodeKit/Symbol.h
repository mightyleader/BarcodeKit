//
//  Symbol.h
//	Object represents a single character, data or non-data, storing it's attributes and encoding
//  BarcodeKit
//
//  Created by Robert Stearn on 13.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_Symbol_h
#define BarcodeKit_Symbol_h

#include <vector>

using namespace std;

class Symbol
{
	public:
	//Build and destroy
	Symbol( );																					//default constructor
	Symbol( int characterData[ ], int dataLength );												//construct with passed data...
	Symbol( int characterData[ ], int dataLength, int startWith );								//...with data and leading flag...
	Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth );				//...with data, leading flag and ic gap...
	Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth, int ofType );	//...or with everything supplied
	~Symbol( );
	
	//Accessors
	int getLeadingElement( );
	int getIntercharGap( );
	int getSymbolType( );
	vector<int>* getEncodedData( );
	int getForcePostion( );
	
	void setLeadingElement( int le );
	void setIntercharGap( int icg );
	void setSymbolType( int st );
	void setEncodedData( vector<int> const& ec );
	void setForcedPosition( int fp );
	
	
	private:
	//ivars
	int leadingElement;																			//0 for space, 1 for bar
	int intercharacterGap;																		//0..n as multiple of X width
	int symbolType;																				//0,1..4 indicates data or specific non-data type
	vector<int>encodedSymbol;																	//vector of element widths as multiples of X width
	int forcePosition;																			//int value to specify ultimate position in destination array
	
	bool arrayIntoVector( int source[ ], int sourceLength, vector<int> &destination );
};

#endif
