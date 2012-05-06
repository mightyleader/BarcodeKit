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
	this->arrayIntoVector(characterData, dataLength, this->encodedSymbol);
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith )
{
	this->arrayIntoVector(characterData, dataLength, this->encodedSymbol);
	this->leadingElement = startWith;
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth )
{
	this->arrayIntoVector(characterData, dataLength, this->encodedSymbol);
	this->leadingElement = startWith;
	this->intercharacterGap = gapWidth;
}

Symbol::Symbol( int characterData[ ], int dataLength, int startWith, int gapWidth, int ofType )
{
	this->arrayIntoVector(characterData, dataLength, this->encodedSymbol);
	this->leadingElement = startWith;
	this->intercharacterGap = gapWidth;
	this->symbolType = ofType;
}

Symbol::~Symbol( )
{
	
}


#pragma mark --Accessor methods--

int Symbol::getLeadingElement( )
{
	return Symbol::leadingElement;
}

int Symbol::getIntercharGap( )
{
	return Symbol::intercharacterGap;
}

int Symbol::getSymbolType( )
{
	return Symbol::symbolType;
}

vector<int>* Symbol::getEncodedData( )
{
	vector<int> *tempVector = new vector<int>;
	tempVector->insert( tempVector->begin( ), Symbol::encodedSymbol.begin( ), Symbol::encodedSymbol.end( ) );
	return tempVector;
}

int Symbol::getForcePostion( )
{
	return Symbol::forcePosition;
}

int Symbol::getAsciiEquivalent( )
{
	return asciiEquivalent;
}

string Symbol::getTextEquivalent( )
{
	return  textEquivalent;
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

void Symbol::setEncodedData( vector<int> const& ec )
{
    Symbol::encodedSymbol = ec;
}

void Symbol::setForcedPosition( int fp )
{
	Symbol::forcePosition = fp;
}

void Symbol::setAsciiEquivalent( int ae )
{
	Symbol::asciiEquivalent = ae;
}

void Symbol::setTextEquivalent( string &te )
{
	Symbol::textEquivalent = te;
}


#pragma mark --Private internal methods--

void Symbol::arrayIntoVector( int source[ ], int sourceLength, vector<int> &destination )
{
	int iter;
	try
	{
		destination.clear( );							//empty the destination
		destination.resize( sourceLength );				//resize it as we don't know that source and destination are same size
		for ( iter = 0; iter < sourceLength; iter++ )	//loop through the source assigning to the destination
		{
			int holdingVar = source[ iter ];
			destination.assign( iter, holdingVar );
		}
		if ( destination.capacity( ) == 0 )
		{
			throw "Array into Vector failed. Insufficient storage available.";
		}
	}
	catch ( const char* str )
	{
		cerr << str << " Program terminated." << endl;
		exit( 0 );
	}
}