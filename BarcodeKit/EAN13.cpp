//
//  EAN13.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include "EAN13.h"
#include "BaseEANUPC.h"
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

EAN13::EAN13( string *data )
{
	filename = "EANUPC.xml";
	parityFilename = "ParityEAN13.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	parity_xml.parse< 0 >( getXMLToParse( &parityFilename ) );
	setDataLength( -1 ); //variable length symbol
	//verify
	if ( verifyData( data ) ) 
	{
		//check char
		encodeCheckCharacter( data );
		//quiet zones
		encodeQuietZones( );
	}
	else 
	{
		cerr << "Data verification failed" << endl;
	}
}

EAN13::~EAN13( )
{
	
}

void EAN13::encodeSymbol ( const string *data )
{
	string parityRef = data->substr( 0,1 );
	string leftSide = data->substr( 1,6 );
	string rightSide = data->substr( 7,6 );
	
	string searchRef = "parity";
	searchRef = searchRef.append( parityRef );
	xml_node< > *parityNode = parity_xml.first_node( )->first_node( )->next_sibling( )->first_node( searchRef.c_str( ) );
	xml_node< > *node = NULL;
	string parityPattern = parityNode->value( );
	
	cout << "Left: " << leftSide << " Right: " << rightSide << endl;
	cout << "Parity Pattern: " << parityPattern << endl;
	//loop through the left side
	for ( int zz = 0; zz < leftSide.length( ); zz++ ) 
	{
		char aChar = leftSide.at( zz );
		string firstBit = kASCII;
		string secondBit;
		stringstream out;
		out << ( int )aChar;
		secondBit = out.str( );
		out.flush( );
		firstBit.append( secondBit );
		
		node = parsed_xml.first_node( )->first_node( )->next_sibling( )->first_node( firstBit.c_str( ) )->first_node( parityPattern.substr( zz,1 ).c_str( ) );
		
		vector< int > *pattern = stringToVector( node->value( ) );
		Symbol *eSymbol = createSymbol( 0, 0, 0, 0, pattern );
		BaseBarcode::addEncodedSymbol( eSymbol );
	}
	//loop through the right side data
	for ( int aa = 0; aa < rightSide.length( ); aa++ ) 
	{
		char bChar = rightSide.at( aa );
		string firstBit = kASCII;
		string secondBit;
		stringstream out;
		out << ( int )bChar;
		secondBit = out.str( );
		out.flush( );
		firstBit.append( secondBit );
		
		node = parsed_xml.first_node( )->first_node( )->next_sibling( )->first_node( firstBit.c_str( ) )->first_node( "C" );
		vector< int > *pattern = stringToVector( node->value( ) );
		Symbol *eSymbol = createSymbol( 0, 0, 1, 0, pattern );
		BaseBarcode::addEncodedSymbol( eSymbol );
	}
	
	//encodeGuardPatterns( );
}

void EAN13::encodeQuietZones ( )
{
	
}

void EAN13::encodeGuardPatterns( )
{
	
}


void EAN13::setGuardPatterns( string left, string centre, string right )
{
	
}

vector< string > EAN13::getGuardPatterns( )
{
	vector< string > aVector;
	return aVector;
}

vector< int >* EAN13::stringToVector( string aString )
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