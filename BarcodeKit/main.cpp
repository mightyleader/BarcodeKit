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

using namespace std;
using namespace rapidxml;

Symbol* createSymbol( int st, int ic, int le, int fp, vector< int > *aVector );
void testSymbol( Symbol *testSymbol );
char* getXMLToParse( string *fileTitle );
void testDOM ( xml_node< > *node );
vector<string> returnDOMValues( xml_node< > *node );

int main( int argc, const char * argv[ ] )
{
	//****************************
	//** Symbol Class Test Code **
	//****************************
	
	//Unit Test Data for Symbol
	vector< int > *testVector = new vector< int >( );
	testVector->push_back( 1 );
	testVector->push_back( 2 );
	testVector->push_back( 3 );
	testVector->push_back( 4 );
	testVector->push_back( 1 );
	//int st = 1, ic = 1, le = 0, fp = 5;
	
	//unit Test - Symbol
	//Symbol *versionOne = createSymbol( st, ic, le, fp, testVector );
	//testSymbol( versionOne );
	
	delete testVector;
	//End Unit Test - Symbol
	
	//****************************
	//** RapidXML Test Code ******
	//****************************
	
	// Process the file
	string *filename = new string( "xml_test.xml" );
	xml_document< > parsed_xml;
	parsed_xml.parse< 0 >( getXMLToParse( filename ) );
	
	// Test for data characters
	xml_node< > *node = NULL;
	node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( "ascii49" );
	//testDOM( node );
	
	// Test for nondata characters
	node = parsed_xml.first_node( )->first_node( )->next_sibling( )->next_sibling( "non_data_encoding" )->first_node( "guard_centre" );
	//testDOM( node );
	
	// Test for contained value
	node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( )->first_node();
	//testDOM( node );
	
	//*****************************
	//** Putting it all together **
	//*****************************
	
	string *incomingString = new string( "07841669212" );
	
	//make an array of the ascii value of each char in the string
	int stringLength = incomingString->length( );
	int asciiList[ stringLength ];
	//loop thru the data and fill the array with ascii values.
	for ( int ii = 0; ii < stringLength; ii++ ) 
	{
		char eachChar = incomingString->at( ii );
		asciiList[ ii ] = ( int )eachChar;
	}
	
	for ( int jj = 0; jj < stringLength; jj++ ) 
	{
		string firstBit = "ascii";
		//concatenate strings to get tag name, a serious hack but couldnt get boost working
		int kk = asciiList[ jj ];
		string secondBit;
		stringstream out;
		out << kk;
		secondBit = out.str( );
		firstBit.append( secondBit );
		
		node = parsed_xml.first_node( )->first_node( )->next_sibling( "data_encoding" )->first_node( firstBit.c_str( ) );
		
		// IF C THEN DO C THINGS
		//use the offset and the composite value of JJ & JJ+1 (compensating for overflow) 
		//build an asciixx ref. and set the node to that value
		//otherwise use the normal method for A or B and off to the races.
		//Except with loops not jumps
		
		//*******SET C SPECIFIC**********
		//which set are we taking the char from? THIS IS FOR BASE128 DERIVED CLASSES ONLY
		//Use Set C? 
		char eachChar = incomingString->at( jj );
		char nextChar = incomingString->at( jj + 1 ); //add buffer overflow correction
		int charSetToRef = 0;
		if ( isdigit( eachChar ) && isdigit( nextChar )  ) //Test for consecutive digits
		{
			charSetToRef = 3;
			//TODO increment counter by 1 and store the concat. numbers into a string and use it to determine pattern 
		}
		
		//ELSE IF A OR B DO A/B THINGS
		
		//*******A & B FROM HERE*********
		
		//get the values for the tag back as a vector
		vector<string> returnedData = returnDOMValues( node );
		cout << returnedData.at( 0 ) << " - " << returnedData.at( 1 ) << " - " << returnedData.at( 2 ) << " - " << returnedData.at( 3 ) << endl; //DEBUG
		
		
		//Use Set B?
		if ( returnedData.at( 1 ) == "nil" ) 
		{
			charSetToRef = 2;
		}
		//OK, Set A it is.
		else 
		{
			charSetToRef = 1;
		}
		
		vector< int > *pattern = new vector< int >;
		for ( int ll = 0; ll < returnedData.at( charSetToRef ).length( ) ; ll++)
		{
			char eachCharFromResult = returnedData.at( charSetToRef )[ ll ];
			int temp = atoi( &eachCharFromResult );
			pattern->push_back( temp );
		}
		
		//******END A & B SPECIFIC CODE******
		
		//UNITE A B C PATHS TO CREATE SYMBOL FROM OUTPUT OF CONDITIONAL

		//use them to create a Symbol
		Symbol *aSymbol = createSymbol( 1, 0, 1, 0, pattern ); //Default values for Base128 and BaseEANUPC except data
		
		//test the symbol object
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
	cout << node->name( ) << ":";
	xml_node< > *datanode = node->first_node( );
	while ( datanode != 0 ) 
	{
		cout << " - " << datanode->name( );
		xml_node< > *childnode = datanode->first_node( );
		while ( childnode != 0 ) 
		{
			cout << childnode->name( ) << " is " << childnode->value( );
			string aValue = childnode->value( );
			returnValues->push_back( aValue );
			childnode = childnode->next_sibling( );
		}
		datanode = datanode->next_sibling( );
	}
	cout << endl;
	node = node->next_sibling( );
	
	return *returnValues;
}



