//
//  Code128.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <string>
#include "Code128.h"
#include "Symbol.h"
#include "rapidxml.hpp"

#define kModulus 103
#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Code128::Code128( string *data )
{
	BaseBarcode::setCheckcharModulus( kModulus );
	filename = "xml_test.xml";
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


Code128::~Code128( )
{
	
}


bool Code128::verifyContent ( const string *content )
{
//	//** setup acceptable content **
//	string ASCIIstring = "$%* +-./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	set< char > setOfASCII;
//	set< char > ::iterator iter;
//	for ( int nn = 0; nn < ASCIIstring.length( ); nn++ ) 
//	{
//		setOfASCII.insert( ASCIIstring.at( nn ) );
//	}
//	//** check the incoming string **
//	for ( int nn = 0; nn < content->length( ); nn++ ) 
//	{
//		iter = setOfASCII.find( content->at( nn ) );
//		if (iter == setOfASCII.end( ) ) 
//		{
//			cerr << "You are trying to encode " << content->at( nn ) << " which is not supported by this barcode type." << endl;
//			return false;
//		}
//	}
	return true;   
}


void Code128::encodeStartStop ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "start_char" )->first_node( "Code128" );
	returnedData = node->value( );
	
	vector< int > *pattern = stringToVector( returnedData );
	
	Symbol *startstopSymbol = createSymbol( 4, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( startstopSymbol, 0 );
	BaseBarcode::addEncodedSymbol( startstopSymbol, BaseBarcode::encodedSymbols.size( ) );
}


void Code128::encodeQuietZones ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "quietzone_left" )->first_node( "Code128" );
	returnedData = node->value( );
	
	int width = atoi( returnedData.c_str( ) );
	vector< int > *pattern = new vector< int >;
	pattern->push_back( width );
	
	Symbol *quietSymbol = createSymbol( 2, 1, 1, 0, pattern );
	BaseBarcode::addEncodedSymbol( quietSymbol, 0 );
	BaseBarcode::addEncodedSymbol( quietSymbol, BaseBarcode::encodedSymbols.size( ) );
}


void Code128::encodeCheckCharacter ( const string *data )
{
//	int accumulator = 0;
//	for ( int bb = 0; bb < data->length( ); bb++ ) 
//	{
//		char aChar = data->at( bb );
//		int returnedINT = ( int )aChar;
//		accumulator = accumulator + returnedINT;
//	}
//	
//	int modulo = accumulator % BaseBarcode::getCheckcharModulus( );
//	char returnChar =  modulo;
//	
//	xml_node< > *node = NULL;
//	
//	//**int to string using streams - inefficient but standard**
//	string returnedData;
//	string firstBit = kASCII;
//	string secondBit;
//	stringstream out;
//	out << ( int )returnChar;
//	secondBit = out.str( );
//	out.flush( );
//	firstBit.append( secondBit );
//	
//	node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "Code128" );
//	returnedData = node->value( );
//	vector< int > *pattern = stringToVector( returnedData );
//	
//	Symbol *aSymbol = createSymbol( 1, 1, 1, 0, pattern ); 
//	BaseBarcode::addEncodedSymbol( aSymbol, BaseBarcode::encodedSymbols.size( ) );
//	
//	delete pattern;
}


int Code128::returnCheckCharASCII(  )
{
	return 0;
}


vector< int >* Code128::stringToVector( string aString )
{
	vector< int > *pattern = new vector< int >;
	for ( int ll = 0; ll < aString.length( ) ; ll++ )
	{
		char eachCharFromResult = aString.at( ll );
		int temp = atoi( &eachCharFromResult );
		pattern->push_back( temp );
	}
	return pattern;
}