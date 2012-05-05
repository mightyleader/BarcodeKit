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
#define kModulus 10

using namespace std;
using namespace rapidxml;

Interleaved2of5::Interleaved2of5( string *data )
{
	BaseBarcode::setCheckcharModulus( kModulus );
	filename = "Basic.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	setDataLength( -1 ); //variable length symbol
	//verify
	if ( verifyData( data ) ) 
	{
		//check char
		encodeCheckCharacter( data );
		//data
		//encodeSymbol( data );
		//start/stop
		//encodeStartStop( );
		//quiet zones
		//encodeQuietZones( );
	}
	else 
	{
		cerr << "Data verification failed" << endl;
	}
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
	xml_node< > *node = NULL;
	
	for ( int ii = 0; ii < data->length( ); ii++ ) 
	{
		char char1 = data->at( ii );
		char char2 = data->at( ii + 1 );
		string returnedData1, returnedData2;
		
		//node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "Code39" );
		
		
		
		
		ii++;
	}


	
	
	
	
	
	
	//intertwingle them into a string
	//string to vector of ints
	//create symbol etc...
}

void Interleaved2of5::encodeStartStop ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "start_char" )->first_node( "Interleaved2of5" );
	returnedData = node->value( );
	
	vector< int > *pattern = stringToVector( returnedData );
	
	Symbol *startstopSymbol = createSymbol( 4, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( startstopSymbol, 0 );
	BaseBarcode::addEncodedSymbol( startstopSymbol, BaseBarcode::encodedSymbols.size( ) );
}

void Interleaved2of5::encodeQuietZones ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "quietzone_left" )->first_node( "Interleaved2of5" );
	returnedData = node->value( );
	
	int width = atoi( returnedData.c_str( ) );
	vector< int > *pattern = new vector< int >;
	pattern->push_back( width );
	
	Symbol *quietSymbol = createSymbol( 2, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( quietSymbol, 0 );
	BaseBarcode::addEncodedSymbol( quietSymbol, BaseBarcode::encodedSymbols.size( ) );
}

void Interleaved2of5::encodeCheckCharacter ( const string *data )
{
	int accum1 = 0, accum2 = 0;
	for ( int cc = data->length( ) - 1; cc > 0; cc-- ) 
	{
		char eachOdd = data->at( cc );
		accum1 = accum1 + atoi( &eachOdd ) ;
		cc--;
	}
	for ( int cc = data->length( ) - 1; cc > 0; cc--)
	{
		cc--;
		char eachEven = data->at( cc );
		accum2 = accum2 + atoi( &eachEven );
	}
	
	accum1 = ( accum1 * 3 ) + accum2;
	int checkchar = (char)kModulus -  ( accum1 % kModulus );
	
	string suffix;
	stringstream output;
	output << checkchar;
	suffix = output.str( );
	output.flush( );
	
	string *newString = new string ( *data );
	
	newString->append( suffix );
	
	if ( newString->length( ) % 2 == 1 ) 
	{
		newString->insert( newString->begin( ), '0' );
	}
	
	encodeSymbol( newString );
}

vector< int >* Interleaved2of5::stringToVector( string aString )
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

