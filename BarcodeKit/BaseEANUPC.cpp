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
	int accumulator = 0;
	
	for ( int yy = 0; yy < data->length( ); yy++ ) 
	{
		//cout << yy << ". ";
		int index = data->length( ) - 1 - yy;
		string tempString = data->substr( index ,1 );
		char eachChar = tempString.at( 0 );
		int eachINT = atoi( &eachChar );
		//cout << " " << eachINT << " * ";
		if ( eachINT % 2 == 0 ) 
		{
			accumulator = accumulator + ( eachINT * 3 );
			//cout << "3 = ";
		} 
		else 
		{
			accumulator = accumulator + eachINT;
			//cout << "1 = ";
		}
		//cout << accumulator << endl;
	}
	//cout << "Total: " << accumulator << endl;
	int result = 0;
	if ( (accumulator % 10 ) == 0 ) 
	{
		result = 0;
	} else 
	{
		result = 10 - ( accumulator % 10 );
	}
	
	string suffix;
	stringstream output4;
	output4 << result;
	suffix = output4.str( );
	output4.flush( );
	string *newString = new string ( *data );
	//cout << "Check Digit: " << suffix << endl;
	newString->append( suffix );
	encodeSymbol( newString );
}

