//
//  Interleaved2of5.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 04.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <string>
#include "Interleaved2of5.h"
#include "Symbol.h"
#include "rapidxml.hpp"

#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Interleaved2of5::Interleaved2of5( string *data )
{
	//verify
	verifyData( data );
	//data
	encodeSymbol( data );
	//start/stop
	encodeStartStop( );
	//quiet zones
	encodeQuietZones( );
	//check char
	encodeCheckCharacter( data );
}

Interleaved2of5::~Interleaved2of5( )
{
	
}

bool Interleaved2of5::verifyContent ( const string *content )
{
	string ASCIIstring = "0123456789";
	set< char > setOfASCII;
	set< char > ::iterator iter;
	for ( int nn = 0; nn < ASCIIstring.length( ); nn++ ) 
	{
		setOfASCII.insert( ASCIIstring.at( nn ) );
	}
	for ( int nn = 0; nn < content->length( ); nn++ ) 
	{
		iter = setOfASCII.find( content->at( nn ) );
		if (iter == setOfASCII.end( ) ) 
		{
			cerr << "You are trying to encode " << content->at( nn ) << " which is not supported by this barcode type." << endl;
			return false;
		}
	}
	return true; 
}

void Interleaved2of5::encodeSymbol ( const string *data )
{
	
}

void Interleaved2of5::encodeStartStop ( )
{
	
}

void Interleaved2of5::encodeQuietZones ( )
{
	
}

void Interleaved2of5::encodeCheckCharacter ( const string *data )
{
	
}

