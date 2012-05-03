//
//  main.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 09.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Symbol.h"
#include "rapidxml.hpp"

#define kOffsetASCII 32
#define kSetA 1
#define kSetB 2
#define kSetC 3
#define kASCII "ascii"

using namespace std;
using namespace rapidxml;

Symbol* createSymbol( int st, int ic, int le, int fp, vector< int > *aVector );
void testSymbol( Symbol *testSymbol );
char* getXMLToParse( string *fileTitle );
void testDOM ( xml_node< > *node );
vector<string> returnDOMValues( xml_node< > *node );

int main( int argc, const char * argv[ ] )
{	
	//*****************************
	//** Putting it all together **
	//*****************************
	cout << "Start" << endl;
	string *filename = new string( "xml_test.xml" );
	xml_document< > parsed_xml;
	cout << "Parsing starts..." << endl;
	parsed_xml.parse< 0 >( getXMLToParse( filename ) );
	cout << "...and ends.\n" << endl;
	xml_node< > *node = NULL;
	xml_node< > *special = NULL;
	
	string *incomingString = new string( "ABC12345abc" );
	int previousCharSet = kSetA; //** default to using set A first **
	
	//make an array of the ascii value of each char in the string
	int stringLength = incomingString->length( );
	int asciiList[ stringLength ];
	//loop thru the data and fill the array with its ascii values.
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
		//cout << "ASCII Code is: " << kk << " for: " << incomingString->at( jj ) << endl;
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
			//cout << "ASCII Code is: " << (int)incomingString->at( jj + 1 ) << " for: " << incomingString->at( jj + 1 ) << endl;
			string setCAscii = ASCIIRef.append( &firstDigit );
			string shortString = setCAscii.substr( 5, 2 );
			int offsetASCIIValue = std::atoi( shortString.c_str( ) )  + kOffsetASCII;

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
		
		//cout << "Using Set " << charSetToRef << ", was using Set " << previousCharSet << endl;
		
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
			//cout << "FROM: " << prevCharSetRefAsString << endl;
			
			//** Which char set are we going to? We can shoot to the exact place in the DOM **
			string charSettoRefAsString;
			switch ( charSetToRef ) 
			{
				case 1:
					charSettoRefAsString =  "CodeA";
					break;
				case 2:
					charSettoRefAsString = "CodeB";
					break;
				case 3:
					charSettoRefAsString = "CodeC";
					break;
			}
			//cout << "TO: " << charSettoRefAsString << endl;
			
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
			
			Symbol *bSymbol = createSymbol( 4, 0, 1, 0, specialPattern );
			cout << "*** CHANGING SET SYMBOL ***" << endl;
			testSymbol( bSymbol );
			
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
		
		// Create and test symbol
		Symbol *aSymbol = createSymbol( 1, 0, 1, 0, pattern ); //Default values for Base128 and BaseEANUPC except data
		cout << "*** DATA SYMBOL ***" << endl;
		testSymbol( aSymbol );
		
		delete pattern;
	}
    return 0;
}


//******************************
//*** TESTING FUNCTIONS ********
//******************************

Symbol* createSymbol( int st, int ic, int le, int fp, vector<int> *aVector ) //make a new symbol with passed values
{
	Symbol *versionOne = new Symbol( );
	versionOne->setSymbolType( st );
	versionOne->setIntercharGap( ic );
	versionOne->setLeadingElement( le );
	versionOne->setForcedPosition( fp );
	versionOne->setEncodedData( *aVector );
	return versionOne;
}

void testSymbol( Symbol *testSymbol ) //Output the values of a Symbol object to standard output
{
	cout << "Unit Test - Symbol" << endl;
	cout << "Symbol Type: " << testSymbol->getSymbolType( ) << endl;
	cout << "Leading Element: " << testSymbol->getLeadingElement( ) << endl;
	cout << "IC Gap: " << testSymbol->getIntercharGap( ) << endl;
	cout << "Force Position: " << testSymbol->getForcePostion( ) << endl;
	cout << "Data: ";
	for ( int ii = 0; ii < testSymbol->getEncodedData( )->size( ); ii++ ) 
	{
		cout << testSymbol->getEncodedData( )->at( ii );
	}
	cout << endl;
	cout << endl;
}

char* getXMLToParse( string *fileTitle ) //Safely get the XML file into a c_string
{
	char *ft = new char[ fileTitle->length( ) + 1 ];
	strcpy( ft, fileTitle->c_str( ) );
	ifstream xmlfile ( ft, ios::in );
	
	vector<string> xmlcontent;
	string xmlentry;
	string xmltoparse;
	
	if ( xmlfile.is_open( ) )							//open the file
	{
		while ( getline( xmlfile, xmlentry ) )			//get the data
		{
			xmlcontent.push_back( xmlentry + "\n" );	//add data to vector
		}
		xmlfile.close( );
		
		for ( int i = 0; i < xmlcontent.size( ); i++ )	//iterate through vector into string
		{
			xmltoparse += xmlcontent[ i ];
		}
	}
	
	char * cxml = new char [ xmltoparse.size( ) + 1 ];	//copy string into cstring
	strcpy ( cxml, xmltoparse.c_str( ) );
	
	return cxml;
}

void testDOM ( xml_node< > *node ) //Test contents of a single named or unnamed node in the DOM
{
		cout << node->name( ) << ":";
		xml_node< > *datanode = node->first_node( );
		while (datanode != 0) 
		{
			cout << " - " << datanode->name( );
			xml_node< > *childnode = datanode->first_node( );
			while (childnode != 0) 
			{
				cout << childnode->name( ) << " is " << childnode->value( );
				childnode = childnode->next_sibling( );
			}
			datanode = datanode->next_sibling();
		}
		cout << endl;
		node = node->next_sibling( );
}

vector<string> returnDOMValues( xml_node< > *node ) //Return contents of a single named or unnamed node in the DOM
{
	vector<string> *returnValues = new vector<string>;
	//cout << node->name( ) << ":";
	xml_node< > *datanode = node->first_node( );
	while ( datanode != 0 ) 
	{
		//cout << " - " << datanode->name( );
		xml_node< > *childnode = datanode->first_node( );
		while ( childnode != 0 ) 
		{
			//cout << childnode->name( ) << " is " << childnode->value( );
			string aValue = childnode->value( );
			returnValues->push_back( aValue );
			childnode = childnode->next_sibling( );
		}
		datanode = datanode->next_sibling( );
	}
	//cout << endl;
	node = node->next_sibling( );
	
	return *returnValues;
}



