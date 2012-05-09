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
#define kPatternA 1
#define kPatternB 2
#define kPatternC 3
#define kPatternD 4

UPCE::UPCE( string *data )
{
	filename = "EANUPC.xml";
	checkFilename = "CheckUPCE.xml";
	parsed_xml.parse< 0 >( getXMLToParse( &filename ) );
	parity_xml.parse< 0 >( getXMLToParse( &checkFilename ) );
	setDataLength( 11 );
	
	//verify
	if ( verifyData( data ) ) 
	{
		xml_node< > *gpnode = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( "non_data_encoding" );
		xml_node< > *rightnode = gpnode->first_node( "guard_right" )->first_node( "UPCE" );
		string right =  rightnode->value( );
		xml_node< > *leftnode = gpnode->first_node( "guard_left" )->first_node( "UPCE" );
		string left =  leftnode->value( );
		setGuardPatterns( left, "nothing", right );
		
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


bool UPCE::verifyContent ( const string *content )
{
	//leading zero
	if ( content->at( 0 ) != '0' ) 
	{
		cout << "failed on leading zero" << endl;
		return false;
	}
	//characters in range
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
	
	//zero suppression
	if ( !isZeroSuppresible( content ) ) 
	{
		return false;
	}
	
	//cout << "Passed content check" << endl;
	return true;
}


string* UPCE::zeroSuppression( const string *data )
{
	//** A little ugly but serviceable - replace with XML data storage/iteration?**
	string *zsString = new string( );
	switch ( getZSPattern( ) ) 
	{
		case kPatternA:
			zsString->push_back( data->at( 1 ) );
			zsString->push_back( data->at( 2 ) );
			zsString->push_back( data->at( 3 ) );
			zsString->push_back( data->at( 4 ) );
			zsString->push_back( data->at( 5 ) );
			zsString->push_back( data->at( 10 ) );
			break;
		case kPatternB:
			zsString->push_back( data->at( 1 ) );
			zsString->push_back( data->at( 2 ) );
			zsString->push_back( data->at( 3 ) );
			zsString->push_back( data->at( 4 ) );
			zsString->push_back( data->at( 10 ) );
			zsString->push_back( '4' );
			break;
		case kPatternC:
			zsString->push_back( data->at( 1 ) );
			zsString->push_back( data->at( 2 ) );
			zsString->push_back( data->at( 8 ) );
			zsString->push_back( data->at( 9 ) );
			zsString->push_back( data->at( 10 ) );
			zsString->push_back( data->at( 3 ) );
			break;
		case kPatternD:
			zsString->push_back( data->at( 1 ) );
			zsString->push_back( data->at( 2 ) );
			zsString->push_back( data->at( 3 ) );
			zsString->push_back( data->at( 9 ) );
			zsString->push_back( data->at( 10 ) );
			zsString->push_back( '3' );
			break;
		default:
			break;
	}
	return zsString;
}


bool UPCE::isZeroSuppresible( const string *data )
{
	vector< int	> *test = stringToVector( *data );
	if ( test->at( 6 ) == 0 && test->at( 7 ) == 0 && test->at( 8 ) == 0 && test->at( 9 ) == 0 && ( test->at( 10 ) >= 5 && test->at( 10 ) <= 9 ) ) 
	{
		setZSPattern( kPatternA );
		return true;
	}
	if ( test->at( 5 ) == 0 && test->at( 6 ) == 0 && test->at( 7 ) == 0 && test->at( 8 ) == 0 && test->at( 9 ) == 0 ) 
	{
		setZSPattern( kPatternB );
		return true;
	}
	if ( test->at( 4 ) == 0 && test->at( 5 ) == 0 && test->at( 6 ) == 0 && test->at( 7 ) == 0 && ( test->at( 3 ) >= 0 && test->at( 3 ) <= 2 ) ) 
	{
		setZSPattern( kPatternC );
		return true;
	}
	if ( test->at( 4 ) == 0 && test->at( 5 ) == 0 && test->at( 6 ) == 0 && test->at( 7 ) == 0 && test->at( 8 ) == 0 && ( test->at( 3 ) >= 3 && test->at( 3 ) <= 9 ) ) 
	{
		setZSPattern( kPatternD );
		return true;
	}
	delete test;
	return false;
}


int UPCE::getZSPattern( )
{
	//** 1 = pattern A, 2 = pattern B, 3 = pattern C, 4 = pattern D
	return zsPattern;
}


void UPCE::setZSPattern( int pattern )
{
	zsPattern = pattern;
}


//void UPCE::encodeCheckCharacter ( const string *data )
//{
//	int accumulator = 0;
//	
//	for ( int yy = 0; yy < data->length( ); yy++ ) 
//	{
//		int index = data->length( ) - 1 - yy;
//		string tempString = data->substr( index ,1 );
//		char eachChar = tempString.at( 0 );
//		int eachINT = atoi( &eachChar );
//		if ( eachINT % 2 == 0 ) 
//		{
//			accumulator = accumulator + ( eachINT * 3 );
//		} 
//		else 
//		{
//			accumulator = accumulator + eachINT;
//		}
//	}
//
//	int result = 0;
//	if ( (accumulator % 10 ) == 0 ) 
//	{
//		result = 0;
//	} else 
//	{
//		result = 10 - ( accumulator % 10 );
//	}
//	
//	string suffix;
//	stringstream output4;
//	output4 << result;
//	suffix = output4.str( );
//	output4.flush( );
//	string *newString = new string ( *data );
//	//cout << "Check Digit: " << suffix << endl; //DEBUG
//	newString->append( suffix );
//	cout << *newString << endl;
//	completedDataString = *newString;
//	encodeSymbol( newString );
//}


void UPCE::encodeSymbol ( const string *content )
{
	string *data = zeroSuppression( content );
	string temp = *data;
	temp.append( &completedDataString.at( completedDataString.length( ) - 1 ) );
	completedDataString = temp;
	cout << completedDataString << endl;
	string parityRef = content->substr( content->length( ) - 1,1 );
	string searchRef = "check";
	searchRef = searchRef.append( parityRef );
	xml_node< > *parityNode = parity_xml.first_node( )->first_node( )->next_sibling( )->first_node( searchRef.c_str( ) );
	xml_node< > *node = NULL;
	string parityPattern = parityNode->value( );
	
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
				le = 0;
				pos = UPCE::getEncodedSymbols( ).size( );
				break;
			default:
				break;
		}
		Symbol *gpSymbol = createSymbol( 3, 0, le, 0, pattern );
		BaseBarcode::addEncodedSymbol( gpSymbol, pos );
	}
}


void UPCE::setGuardPatterns( string left, string centre, string right )
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