//
//  Codabar.cpp
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
#include "Codabar.h"
#include "Symbol.h"
#include "rapidxml.hpp"

#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Codabar::Codabar( string *data )
{
	//verify
	verifyData( data );
	//quiet zones
	encodeQuietZones( );
	//start/stop
	encodeStartStop( );
	//data
	encodeSymbol( data );
	//check char
	encodeCheckCharacter( data );
}

Codabar::~Codabar( )
{
	
}

bool Codabar::verifyContent ( const string *content )
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
			return false;
		}
	}
	return true; 
}

void Codabar::encodeSymbol ( const string *data )
{
	
}

void Codabar::encodeStartStop ( )
{
	
}

void Codabar::encodeQuietZones ( )
{
	
}

void Codabar::encodeCheckCharacter ( const string *data )
{
	
}


