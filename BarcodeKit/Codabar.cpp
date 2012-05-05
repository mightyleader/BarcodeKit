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

Codabar::Codabar( )
{
	
}

Codabar::Codabar( string *data )
{
	//verify
	verifyData( data );
	//data
	encodeSymbol( data );
	//check char
	encodeCheckCharacter( data );
	//start/stop
	encodeStartStop( );
	//quiet zones
	encodeQuietZones( );
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
			cerr << "You are trying to encode " << content->at( nn ) << " which is not supported by this barcode type." << endl;
			return false;
		}
	}
	return true; 
}

void Codabar::encodeSymbol ( const string *data )
{
	string *filename = new string( "Basic.xml" );
	xml_document< > parsed_xml;
	parsed_xml.parse< 0 >( getXMLToParse( filename ) );
	xml_node< > *node = NULL;
	
	//** make an array of the ascii value of each char in the string **
	const string *incomingString = data;
	int stringLength = incomingString->length( );
	int asciiList[ stringLength ];
	
	//** loop thru the data and fill the array with its ascii values. **
	for ( int ii = 0; ii < stringLength; ii++ ) 
	{
		unsigned char eachChar = incomingString->at( ii );
		asciiList[ ii ] = ( int )eachChar;
	}
	
	for ( int jj = 0; jj < stringLength; ++jj ) 
	{
		//** concatenate strings to get tag name, a serious hack but couldnt get boost working and itoa is non-standard c++
		string firstBit = kASCII;
		int kk = asciiList[ jj ];
		string secondBit;
		stringstream out;
		out << kk;
		secondBit = out.str( );
		out.flush( );
		firstBit.append( secondBit );
		
		string ASCIIRef = kASCII;
		string returnedData;
		
		node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "CodaBar" );
		returnedData = node->value( );
		
		vector< int > *pattern = new vector< int >;
		for ( int ll = 0; ll < returnedData.length( ) ; ll++)
		{
			char eachCharFromResult = returnedData.at( ll );
			int temp = atoi( &eachCharFromResult );
			temp++; //to bring it up to standard 1 for narrow, 2X...NX for wide
			pattern->push_back( temp );
		}
		
		// Create and store data symbol
		Symbol *aSymbol = createSymbol( 1, 1, 1, 0, pattern ); 
		BaseBarcode::addEncodedSymbol( aSymbol );
		
		delete pattern;
	}
	
	
	
}

void Codabar::encodeStartStop ( )
{
	
}

void Codabar::encodeQuietZones ( )
{
	
}

void Codabar::encodeCheckCharacter ( const string *data )
{
	cout << "Whatever" << endl;
}


