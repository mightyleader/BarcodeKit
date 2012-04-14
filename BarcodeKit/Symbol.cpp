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
#include <vector>

using namespace std;

#pragma mark --Constructor methods--

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


#pragma mark --Accessor methods--

int Symbol::getLeadingElement( )
{
	return 1;
}

int Symbol::getIntercharGap( )
{
	return 1;
}

int Symbol::getSymbolType( )
{
	return 1;
}

vector<int>* Symbol::getEncodedData( )
{
	return 0;
}

int Symbol::getForcePostion( )
{
	return 1;
}

void Symbol::setLeadingElement( int le )
{
	Symbol::leadingElement = le;
}

void Symbol::setIntercharGap( int icg )
{
	Symbol::intercharacterGap = icg;
}

void Symbol::setSymbolType( int st )
{
	Symbol::symbolType = st;
}

void Symbol::setEncodedData( vector<int>* ec )
{
	
}

void Symbol::setForcedPosition( int fp )
{
	
}


#pragma mark --Private internal methods--

bool Symbol::arrayIntoVector( int source[ ], int sourceLength, vector<int> destination )
{
	int iter;
	destination.clear();							//empty the destination
	destination.resize(sourceLength);				//resize it as we don't know that source and destination are same size
	for ( iter = 0; iter < sourceLength; iter++ )	//loop through the source assigning to the destination
	{
		int holdingVar = source[iter];
		destination.assign(iter, holdingVar);
	}
	
	return 1;
}