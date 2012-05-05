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

#define kAlphaOffset 55
#define kNumericOffset 48
#define kModulus 43

#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Code39::Code39( string *data )
{
	BaseBarcode::setCheckcharModulus( kModulus );
	filename = "Basic.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
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
	string ASCIIstring = "$%* +-./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
		
		node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "Code39" );
		returnedData = node->value( );
		vector< int > *pattern = stringToVector( returnedData );
		
		Symbol *aSymbol = createSymbol( 0, 1, 1, 0, pattern ); 
		BaseBarcode::addEncodedSymbol( aSymbol );
		
		delete pattern;
	}
}

void Code39::encodeStartStop ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "start_char" )->first_node( "Code39" );
	returnedData = node->value( );
	
	vector< int > *pattern = stringToVector( returnedData );
	
	Symbol *startstopSymbol = createSymbol( 4, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( startstopSymbol, 0 );
	BaseBarcode::addEncodedSymbol( startstopSymbol, BaseBarcode::encodedSymbols.size( ) );
}

void Code39::encodeQuietZones ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "quietzone_left" )->first_node( "Code39" );
	returnedData = node->value( );
	
	int width = atoi( returnedData.c_str( ) );
	vector< int > *pattern = new vector< int >;
	pattern->push_back( width );
	
	Symbol *quietSymbol = createSymbol( 2, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( quietSymbol, 0 );
	BaseBarcode::addEncodedSymbol( quietSymbol, BaseBarcode::encodedSymbols.size( ) );
}

void Code39::encodeCheckCharacter ( const string *data )
{
	int accumulator = 0;
	for ( int bb = 0; bb < data->length( ); bb++ ) 
	{
		char aChar = data->at( bb );
		int returnedINT = checksumIntForChar( aChar );
		accumulator = accumulator + returnedINT;
	}
	
	int modulo = accumulator % BaseBarcode::getCheckcharModulus( );
	char returnChar = checksumCharForInt( modulo );
	
	xml_node< > *node = NULL;
	
	//**int to string using streams - inefficient but standard**
	string returnedData;
	string firstBit = kASCII;
	string secondBit;
	stringstream out;
	out << ( int )returnChar;
	secondBit = out.str( );
	out.flush( );
	firstBit.append( secondBit );
	
	node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "Code39" );
	returnedData = node->value( );
	vector< int > *pattern = stringToVector( returnedData );
	
	Symbol *aSymbol = createSymbol( 1, 1, 1, 0, pattern ); 
	BaseBarcode::addEncodedSymbol( aSymbol, BaseBarcode::encodedSymbols.size( ) );
	
	delete pattern;
	
}

vector< int >* Code39::stringToVector( string aString )
{
	vector< int > *pattern = new vector< int >;
	for ( int ll = 0; ll < aString.length( ) ; ll++ )
	{
		char eachCharFromResult = aString.at( ll );
		int temp = atoi( &eachCharFromResult );
		temp++; //** to bring it up to standard 1 for narrow, 2X...NX for wide **
		pattern->push_back( temp );
	}
	return pattern;
}

int Code39::checksumIntForChar( int aChar )
{
	if ( isdigit( ( char )aChar ) ) 
	{
		return aChar - kNumericOffset;
	} 
	else if ( isalpha( aChar ) ) 
	{
		return ( int )aChar - kAlphaOffset;
	}
	else 
	{
		switch ( aChar ) 
		{
			case ' ':
				return 38;
				break;
			case '$':
				return 39;
				break;
			case '%':
				return 42;
				break;
			case '+':
				return 41;
				break;
			case '-':
				return 36;
				break;
			case '.':
				return 37;
				break;
			case '/':
				return 40;
				break;
			default:
				break;
		}
	}
	return 0;
}

char Code39::checksumCharForInt( int anInt )
{
	if ( anInt >= 0 && anInt <= 9 ) 
	{
		return anInt + kNumericOffset;
	} 
	else if ( anInt >= 10 && anInt <= 35 ) 
	{
		return anInt + kAlphaOffset;
	}
	else 
	{
		switch ( anInt ) {
			case 36:
				return 45;
				break;
			case 37:
				return 46;
				break;
			case 38:
				return 32;
				break;
			case 39:
				return 36;
				break;
			case 40:
				return 47;
				break;
			case 41:
				return 43;
				break;
			case 42:
				return 37;
				break;
			default:
				break;
		}
	}
	return 0;
}