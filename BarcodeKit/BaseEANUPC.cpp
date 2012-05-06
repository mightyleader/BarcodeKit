//
//  BaseEANUPC.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include "BaseEANUPC.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <string>
#include "Symbol.h"
#include "rapidxml.hpp"

#define kASCII "ascii"

BaseEANUPC::BaseEANUPC ( )
{
	BaseBarcode::setCheckcharModulus( 10 );
}

BaseEANUPC::~BaseEANUPC ( )
{
	
}

bool BaseEANUPC::verifyContent ( const string *content )
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
	cout << "Passed content check" << endl;
	return true;
}

void BaseEANUPC::encodeSymbol ( const string *data )
{
	
}

void BaseEANUPC::encodeQuietZones ( )
{
	
}

void BaseEANUPC::encodeStartStop( )
{
	
}

void BaseEANUPC::encodeCheckCharacter ( const string *data )
{
	int accumulator;
	
	for ( int yy = 0; yy < data->length( ); yy++ ) 
	{
		int index = data->length( ) - 1 - yy;
		string tempString = data->substr( index ,1 );
		char eachChar = tempString.at( 0 );
		int eachINT = atoi( &eachChar );
		if ( eachINT % 2 == 0 ) 
		{
			accumulator = accumulator + ( eachINT * 3 );
		} 
		else 
		{
			accumulator = accumulator + eachINT;
		}
	}
	int result = 10 - (accumulator % 10 );
	
	string suffix;
	stringstream output;
	output << result;
	suffix = output.str( );
	output.flush( );
	
	string *newString = new string ( *data );
	
	newString->append( suffix );

	encodeSymbol( newString );
}

