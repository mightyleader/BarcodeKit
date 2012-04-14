//
//  Symbol.cpp
//	Object represents a single character, data or non-data, storing it's attributes and encoding
//  BarcodeKit
//
//  Created by Robert Stearn on 13.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include "Symbol.h"
#include <iostream>

using namespace std;

Symbol::Symbol( )
{
	
}

Symbol::Symbol( int characterData[ ], int dataLength )
{
	
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith )
{
	
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth )
{
	
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth, int ofType )
{
	
}

int getLeadingElement( )
{
	return 1;
}

int getIntercharGap( )
{
	return 1;
}

int getSymbolType( )
{
	return 1;
}

vector<int>* getEncodedData( )
{
	
}

int getForcePostion( )
{
	return 1;
}

void setLeadingElement( int le )
{
	
}

void setIntercharGap( int icg )
{
	
}

void setSymbolType( int st )
{
	
}

void setEncodedData( vector<int>* ec )
{
	
}

void setForcedPosition( int fp )
{
	
}

bool Symbol::arrayIntoVector( int source[ ], int sourceLength, vector<int>* destination)
{
	return 1;
}