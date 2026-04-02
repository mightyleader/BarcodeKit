//
//  Symbol.h
//	Object represents a single character, data or non-data, storing its attributes and encoding
//  BarcodeKit
//
//  Created by Robert Stearn on 13.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Symbol_h
#define Symbol_h

#include <vector>
#include <string>

class Symbol
{
	public:
	//Build and destroy
	Symbol( );																					//default constructor
	Symbol( int characterData[ ], int dataLength );												//construct with passed data...
	Symbol( int characterData[ ], int dataLength, int startWith );								//...with data and leading flag...
	Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth );				//...with data, leading flag and ic gap...
	Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth, int ofType );	//...or with everything supplied
	//TODO add constructors for new ivars
	~Symbol( );

	//Accessors
	int getLeadingElement( );
	int getIntercharGap( );
	int getSymbolType( );
	std::vector<int>* getEncodedData( );
	int getForcePosition( );
	int getAsciiEquivalent( );
	std::string getTextEquivalent( );

	void setLeadingElement( int le );
	void setIntercharGap( int icg );
	void setSymbolType( int st );
	void setEncodedData( std::vector<int> const& ec );
	void setForcedPosition( int fp );
	void setAsciiEquivalent( int ae );
	void setTextEquivalent( std::string &te );

	private:
	//ivars
	int leadingElement;																			//0 for space, 1 for bar
	int intercharacterGap;																		//0..n as multiple of X width
	int symbolType;																				//0,1..4 indicates data or specific non-data type
	std::vector<int> encodedSymbol;																//vector of element widths as multiples of X width
	int forcePosition;																			//int value to specify ultimate position in destination array
	int asciiEquivalent;
	std::string textEquivalent;

	void arrayIntoVector( int source[ ], int sourceLength, std::vector<int> &destination );	//since we do this in all the constructors, spin it out
};

#endif
