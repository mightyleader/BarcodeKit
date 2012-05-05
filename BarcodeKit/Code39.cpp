//
//  Code39.cpp
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
#include "Code39.h"
#include "Symbol.h"
#include "rapidxml.hpp"

#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Code39::Code39( string *data )
{
	setDataLength( -1 ); //variable length symbol
	//verify
	if ( verifyData( data ) )
	{
		//data
		encodeSymbol( data );
		//check char
		encodeCheckCharacter( data );
		//start/stop
		encodeStartStop( );
		//quiet zones
		encodeQuietZones( ); 
	}
	else 
	{
		cerr << "Data verification failed" << endl;
	}
}

Code39::~Code39( )
{
	
}

bool Code39::verifyContent ( const string *content )
{
	//** setup acceptable content **
	string ASCIIstring = "0123456789";
	set< char > setOfASCII;
	set< char > ::iterator iter;
	for ( int nn = 0; nn < ASCIIstring.length( ); nn++ ) 
	{
		setOfASCII.insert( ASCIIstring.at( nn ) );
	}
	//** check the incoming string **
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

void Code39::encodeSymbol ( const string *data )
{
	
}

void Code39::encodeStartStop ( )
{
	
}

void Code39::encodeQuietZones ( )
{
	
}

void Code39::encodeCheckCharacter ( const string *data )
{
	
}
