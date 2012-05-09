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
	int multiples[12] = {1,3,1,3,1,3,1,3,1,3,1,3};
	int accumulator = 0;
	int count = NULL;
	int dsl = data->length();
	
	switch (dsl) 
	{
		case 12:
			count = 0;
			break;
		case 11:
			count = 1;
			break;
		case 7:
			count = 5;
			break;
		default:
			break;
	}
	
	for ( int ii = 0; ii < dsl; ii++, count++) 
	{
		string tempstring  = data->substr(ii,1);
		char aChar = tempstring.at(0);
		accumulator += ( atoi(&aChar) * multiples[count] );
	}
	
	int checkdigit = ( 10 - ( accumulator % 10 ) );
	string *newString = new string ( *data );
	
	stringstream output4;
	output4 << checkdigit;
	output4.flush( );
	newString->append( output4.str( ) );
	completedDataString = *newString;
	cout << "Amended string: " << completedDataString << endl;
	encodeSymbol( newString );
}

