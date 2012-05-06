//
//  UPCE.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include "UPCE.h"
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

UPCE::UPCE( string *data )
{
	filename = "EANUPC.xml";
	checkFilename = "CheckUPCE.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	parity_xml.parse< 0 >( getXMLToParse( &checkFilename ) );
	setDataLength( 11 ); //variable length symbol
	
	//verify
	if ( verifyData( data ) ) 
	{
		xml_node< > *gpnode = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( "non_data_encoding" );
		xml_node< > *rightnode = gpnode->first_node( "guard_right" )->first_node( "UPCE" );
		string right =  rightnode->value( );
		xml_node< > *leftnode = gpnode->first_node( "guard_left" )->first_node( "UPCE" );
		string left =  leftnode->value( );
		setGuardPatterns( left, right );
		
		
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


UPCE::~UPCE( )
{
	
}

void UPCE::zeroSuppression( const string *data )
{
	
}

bool UPCE::verifyContent ( const string *content )
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


void UPCE::encodeSymbol ( const string *data )
{
	string parityRef = data->substr( 0,1 );
		
	string searchRef = "check";
	searchRef = searchRef.append( parityRef );
	xml_node< > *parityNode = parity_xml.first_node( )->first_node( )->next_sibling( )->first_node( searchRef.c_str( ) );
	xml_node< > *node = NULL;
	string parityPattern = parityNode->value( );
	
	//loop through the left side
	for ( int zz = 0; zz < data->length( ); zz++ ) 
	{
		char aChar = data->at( zz );
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
		
	UPCE::encodeGuardPatterns( );
}


void UPCE::encodeQuietZones ( )
{
	xml_node< > *QZ = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( )->first_node( "quietzone_left" )->first_node( "UPCE" );
	vector< int > *pattern = new vector< int >;
	
	int left = atoi( QZ->value( ) );
	pattern->push_back( left );
	Symbol *lqzSymbol = createSymbol( 2, 0, 0, 0, pattern );
	BaseBarcode::addEncodedSymbol( lqzSymbol, 0 );
	
	QZ = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( )->first_node( "quietzone_right" )->first_node( "UPCE" );
	vector< int > *patternr = new vector< int >;
	int right = atoi( QZ->value( ) );
	patternr->push_back( right );
	Symbol *rqzSymbol = createSymbol( 2, 0, 0, 0, patternr );
	BaseBarcode::addEncodedSymbol( rqzSymbol, UPCE::getEncodedSymbols( ).size( ) );
}


void UPCE::encodeGuardPatterns( )
{
	for ( int ff = 0; ff < UPCE::getGuardPatterns( ).size( ); ff++) 
	{
		vector< int > *pattern = stringToVector( UPCE::getGuardPatterns( ).at( ff ) );
		int le, pos;
		switch ( ff ) {
			case 0:
				le = 1;
				pos = 0;
				break;
			case 1:
				le = 1;
				pos = UPCE::getEncodedSymbols( ).size( );
				break;
			default:
				break;
		}
		Symbol *gpSymbol = createSymbol( 3, 0, le, 0, pattern );
		BaseBarcode::addEncodedSymbol( gpSymbol, pos );
	}
}


void UPCE::setGuardPatterns( string left, string right )
{
	guardPatterns.push_back( left );
	guardPatterns.push_back( right );
}


vector< string > UPCE::getGuardPatterns( )
{
	return guardPatterns;
}


vector< int >* UPCE::stringToVector( string aString )
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