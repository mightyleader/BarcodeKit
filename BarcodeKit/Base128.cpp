//
//  Base128.cpp
//  BarcodeKit
//	Definitions for Base128 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <string>
#include "Base128.h"
#include "Symbol.h"
#include "rapidxml.hpp"

#define kOffsetASCII 32
#define kSetA 1
#define kSetB 2
#define kSetC 3
#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

#pragma mark --Con/Destructors--

Base128::Base128( )
{

}


Base128::~Base128( )
{
	
}


#pragma mark --Methods--

void Base128::encodeSymbol ( const string *data )
{
	string *filename = new string( "Base128.xml" );
	xml_document< > parsed_xml;
	parsed_xml.parse< 0 >( getXMLToParse( filename ) );
	xml_node< > *node = NULL;
	xml_node< > *special = NULL;
	int offsetASCIIValue;
	const string *incomingString = data;
	int previousCharSet = kSetA; //** default to using set A first **
	
	//** make an array of the ascii value of each char in the string **
	int stringLength = incomingString->length( );
	int asciiList[ stringLength ];
	//** loop thru the data and fill the array with its ascii values. **
	for ( int ii = 0; ii < stringLength; ii++ ) 
	{
		unsigned char eachChar = incomingString->at( ii );
		asciiList[ ii ] = ( int )eachChar;
	}
	
	for ( int jj = 0; jj < stringLength; jj++ ) 
	{
		//** concatenate strings to get tag name, a serious hack but couldnt get boost working and itoa is non-standard c++
		string firstBit = kASCII;
		int kk = asciiList[ jj ];
		offsetASCIIValue = kk;
		string secondBit;
		stringstream out;
		out << kk;
		secondBit = out.str( );
		out.flush( );
		firstBit.append( secondBit );
		int charSetToRef = 1;
		string ASCIIRef = kASCII;
		char secondDigit;
		char firstDigit = incomingString->at( jj );
		
		vector<string> returnedData;
		
		// *** C Char Set ***
		if ( ( jj + 1 ) < stringLength ) 
		{
			secondDigit = incomingString->at( jj + 1 );
		}
		
		if ( isdigit( secondDigit ) && isdigit( firstDigit ) ) 
		{
			string setCAscii = ASCIIRef.append( &firstDigit );
			
			string shortString = setCAscii.substr( 5, 2 );
			offsetASCIIValue = std::atoi( shortString.c_str( ) )  + kOffsetASCII;
			
			stringstream out2;
			out2 << offsetASCIIValue;
			ASCIIRef = kASCII;
			ASCIIRef.append( out2.str( ) );
			out2.flush( );
			
			node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( ASCIIRef.c_str( ) );
			returnedData = returnDOMValues( node );
			charSetToRef = kSetC;
			firstDigit = NULL;
			secondDigit = NULL;
			++jj;
		}
		else //*** A or B Char Sets ***
		{
			node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) );
			returnedData = returnDOMValues( node );
			//** Use Set B? **
			string aSetTest = returnedData.at( kSetA );
			string bSetTest = returnedData.at( kSetB );
			if ( aSetTest == "nil" ) 
			{
				charSetToRef = kSetB;
			}
			//** OK, Set A it is. **
			if ( bSetTest == "nil" )
			{
				charSetToRef = kSetA;
			}
		}
		
		if ( previousCharSet != charSetToRef ) //** Do we need a code set symbol inserted? **
		{
			//** What was the previous character set? Need it as a letter so we convert **
			string prevCharSetRefAsString;
			switch ( previousCharSet ) 
			{
				case 1:
					prevCharSetRefAsString = "A";
					break;
				case 2:
					prevCharSetRefAsString = "B";
					break;
				case 3:
					prevCharSetRefAsString = "C";
					break;
			}
			
			//** Which char set are we going to? We can shoot to the exact place in the DOM **
			string charSettoRefAsString;
			switch ( charSetToRef ) 
			{
				case 1:
					charSettoRefAsString =  "CodeA";
					checkCharList->push_back( 101 );
					break;
				case 2:
					charSettoRefAsString = "CodeB";
					checkCharList->push_back( 100 );
					break;
				case 3:
					charSettoRefAsString = "CodeC";
					checkCharList->push_back( 99 );
					break;
			}
			
			//** Get the data we need back into a vector
			special = parsed_xml.first_node( )->first_node( )->next_sibling( "non_data_encoding" )->first_node( charSettoRefAsString.c_str( ) )->first_node( prevCharSetRefAsString.c_str( ) );
			
			vector< int > *specialPattern = new vector< int >;
			string receivedPattern = special->value( );
			for ( int mm = 0; mm < receivedPattern.length( ); mm++ ) 
			{
				char eachCharFromResult = receivedPattern.at( mm );
				int temp = atoi( &eachCharFromResult );
				specialPattern->push_back( temp );
			}
			
			// Create and store non-data symbol
			Symbol *bSymbol = createSymbol( 5, 0, 1, 0, specialPattern );
			BaseBarcode::addEncodedSymbol( bSymbol );
			
			delete specialPattern;
		}
		
		previousCharSet = charSetToRef;
		
		vector< int > *pattern = new vector< int >;
		for ( int ll = 0; ll < returnedData.at( charSetToRef ).length( ) ; ll++)
		{
			char eachCharFromResult = returnedData.at( charSetToRef )[ ll ];
			int temp = atoi( &eachCharFromResult );
			pattern->push_back( temp );
		}
		
		//fill the vector to prep for the check char work
		switch ( charSetToRef ) 
		{
			case kSetA:
				if ( offsetASCIIValue >= 0 && offsetASCIIValue <= 31 )
				{
					checkCharList->push_back( offsetASCIIValue + 64 );
				} 
				else if ( offsetASCIIValue >= 32 && offsetASCIIValue <= 95) 
				{
					checkCharList->push_back( offsetASCIIValue - 32 );
				}
				break;
			case kSetB:
				if ( offsetASCIIValue >= 32 && offsetASCIIValue <= 127 )
				{
					checkCharList->push_back( offsetASCIIValue - 32 );
				} 
				break;
			case kSetC:
				checkCharList->push_back( offsetASCIIValue - 32 );
				break;
			default:
				break;
		}

		// Create and store data symbol
		Symbol *aSymbol = createSymbol( 0, 0, 1, 0, pattern ); //Default values for Base128 and BaseEANUPC except data
		BaseBarcode::addEncodedSymbol( aSymbol );
		
		delete pattern;
	}
}