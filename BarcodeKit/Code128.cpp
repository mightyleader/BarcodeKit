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
#define kSetA 1
#define kSetB 2
#define kSetC 3
#define kASCII "ascii"
#define kStop "2331112"

using namespace std;
using namespace rapidxml;

Code128::Code128( string *data )
{
	checkCharList = new vector< int >;
	BaseBarcode::setCheckcharModulus( kModulus );
	filename = "Base128.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	setDataLength( -1 ); //variable length symbol
	//verify
	if ( verifyData( data ) )
	{
		//data
		encodeSymbol( data );
		//get Set for first character
		vector< int > *startpattern;
		Symbol *startSymbol;
		//dynamic start symbol creation
		switch ( getSet( data->at( 0 ) ) ) 
		{
			case kSetA:
				startpattern = stringToVector( "211412" );
				startSymbol = createSymbol( 4, 1, 1, 0, startpattern );
				BaseBarcode::addEncodedSymbol( startSymbol, 0 );
				checkCharList->insert( checkCharList->begin( ) , 103 );
				break;
			case kSetB:
				startpattern = stringToVector( "211214" );
				startSymbol = createSymbol( 4, 1, 1, 0, startpattern );
				BaseBarcode::addEncodedSymbol( startSymbol, 0 );
				checkCharList->insert( checkCharList->begin( ) , 104 );
				break;
			case kSetC:
				startpattern = stringToVector( "211232" );
				startSymbol = createSymbol( 4, 1, 1, 0, startpattern );
				BaseBarcode::addEncodedSymbol( startSymbol, 0 );
				checkCharList->insert( checkCharList->begin( ) , 105 );
				break;
			default:
				break;
		}
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
	checkCharList = NULL;
	delete checkCharList;
}


int Code128::getSet( char first )
{
	string firstBit = kASCII;
	string secondBit;
	stringstream ccout;
	ccout << ( int )first;
	secondBit = ccout.str( );
	ccout.flush( );
	firstBit.append( secondBit );
	xml_node< > *firstNode = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "A" );
	string returnedData = firstNode->value( );
	if ( returnedData == "nil" ) 
	{
		firstNode = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "B" );
		returnedData = firstNode->value( );
		if ( returnedData == "nil" ) 
		{
			return kSetC;
		}
		return kSetB; 
	}
	return kSetA;
}


bool Code128::verifyContent ( const string *content )
{
	for ( int nn = 0; nn < content->length( ); nn++ ) 
	{
		char testChar = content->at( nn );
		if ( ( int )testChar < 0 && ( int )testChar > 127 ) 
		{
			cerr << "You are trying to encode " << content->at( nn ) << " which is not supported by this barcode type." << endl;
			return false;
		}
	}
	return true;   
}


void Code128::encodeStartStop ( )
{	
	vector< int > *stoppattern = stringToVector( kStop );
	Symbol *stopSymbol = createSymbol( 4, 1, 1, 0, stoppattern );
	BaseBarcode::addEncodedSymbol( stopSymbol, BaseBarcode::encodedSymbols.size( ) );
}


void Code128::encodeQuietZones ( )
{
	string returnedData;
	xml_node< > *node = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( "quietzone_left" )->first_node( "A" );
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
	xml_node< > *node = NULL;
	vector< int > *pattern = NULL;
	int accumulator = checkCharList->at( 0 );
	//loop through the vector of ascii values....
	for ( int rr = 1; rr < checkCharList->size( ); rr++ ) 
	{
		accumulator = accumulator + ( checkCharList->at( rr ) * ( rr ) );
	}
	
	int modulus = accumulator % 103;
	
	string firstBit = kASCII;
	string secondBit;
	stringstream ccout;
	ccout << modulus;
	secondBit = ccout.str( );
	ccout.flush( );
	firstBit.append( secondBit );
	
	node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "A" );
	string returnedData = node->value( );
	if ( returnedData == "nil" ) 
	{
		node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) )->first_node( "B" );
		returnedData = node->value( );
	} 
	
	pattern = stringToVector( returnedData );
	Symbol *aSymbol = createSymbol( 1, 1, 1, 0, pattern ); 
	BaseBarcode::addEncodedSymbol( aSymbol, BaseBarcode::encodedSymbols.size( ) );
	
	delete pattern;
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