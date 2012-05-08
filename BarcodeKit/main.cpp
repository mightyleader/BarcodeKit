//
//  main.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 09.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include <string>
#include "Symbol.h"
#include "rapidxml.hpp"
#include "Codabar.h"
#include "Code39.h"
#include "Interleaved2of5.h"
#include "EAN13.h"
#include "EAN8.h"
#include "UPCA.h"
#include "UPCE.h"
#include "Code128.h"

using namespace std;
using namespace rapidxml;


//************************
//*** TESTING FUNCTIONS ***
//************************
Symbol* createSymbol( int st, int ic, int le, int fp, vector< int > *aVector );
void testSymbol( Symbol *testSymbol );
char* getXMLToParse( string *fileTitle );
void testDOM ( xml_node< > *node );
vector<string> returnDOMValues( xml_node< > *node );
//************************

int main( int argc, const char * argv[ ] )
{
	string *testString = new string("9037634");
	EAN8 *testBarcode = new EAN8( testString );
	deque< Symbol* > testDeque = testBarcode->getEncodedSymbols( );
	for (int aa = 0; aa < testDeque.size( ); aa++) 
	{
		testSymbol( testDeque.at( aa ) );
	}
	delete testString;
	delete testBarcode;
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
		cout << testSymbol->getEncodedData( )->at( ii ) << " ";
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



