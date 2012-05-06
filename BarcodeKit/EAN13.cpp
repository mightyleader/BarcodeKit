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
#include <stack>
#include <set>
#include <string>
#include "Symbol.h"
#include "rapidxml.hpp"

#define kASCII "ascii"

EAN13::EAN13( string *data )
{
	filename = "EANUPC.xml";
	parityFilename = "ParityEAN13.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	parity_xml.parse< 0 >( getXMLToParse( &parityFilename ) );
	setDataLength( 12 ); //variable length symbol
	
	//verify
	if ( verifyData( data ) ) 
	{
		xml_node< > *gpnode = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( "non_data_encoding" );
		xml_node< > *rightnode = gpnode->first_node( "guard_right" )->first_node( "EANUPC" );
		string right =  rightnode->value( );
		xml_node< > *centrenode = gpnode->first_node( "guard_centre" )->first_node( "EANUPC" );
		string centre =  centrenode->value( );
		xml_node< > *leftnode = gpnode->first_node( "guard_left" )->first_node( "EANUPC" );
		string left =  leftnode->value( );
		setGuardPatterns( left , centre, right );
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
	
	EAN13::encodeGuardPatterns( );
}


void EAN13::encodeQuietZones ( )
{
	xml_node< > *QZ = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( )->first_node( "quietzone_left" )->first_node( "EAN13" );
	vector< int > *pattern = new vector< int >;
	
	int left = atoi( QZ->value( ) );
	pattern->push_back( left );
	Symbol *lqzSymbol = createSymbol( 2, 0, 0, 0, pattern );
	BaseBarcode::addEncodedSymbol( lqzSymbol, 0 );
	
	QZ = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( )->first_node( "quietzone_right" )->first_node( "EAN13" );
	vector< int > *patternr = new vector< int >;
	int right = atoi( QZ->value( ) );
	patternr->push_back( right );
	Symbol *rqzSymbol = createSymbol( 2, 0, 0, 0, patternr );
	BaseBarcode::addEncodedSymbol( rqzSymbol, EAN13::getEncodedSymbols( ).size( ) );
}


void EAN13::encodeGuardPatterns( )
{
	for ( int ff = 0; ff < EAN13::getGuardPatterns( ).size( ); ff++) 
	{
		vector< int > *pattern = stringToVector( EAN13::getGuardPatterns( ).at( ff ) );
		int le, pos;
		switch ( ff ) {
			case 0:
				le = 1;
				pos = 0;
				break;
			case 1:
				le = 0;
				pos = 7;
				break;
			case 2:
				le = 1;
				pos = EAN13::getEncodedSymbols( ).size( );
				break;
			default:
				break;
		}
		Symbol *gpSymbol = createSymbol( 3, 0, le, 0, pattern );
		BaseBarcode::addEncodedSymbol( gpSymbol, pos );
	}
}


void EAN13::setGuardPatterns( string left, string centre, string right )
{
	guardPatterns.push_back( left );
	guardPatterns.push_back( centre );
	guardPatterns.push_back( right );
}


vector< string > EAN13::getGuardPatterns( )
{
	return guardPatterns;
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