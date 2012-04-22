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
#include <string>
#include "Symbol.h"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

int main( int argc, const char * argv[ ] )
{
	//****************************
	//** Symbol Class Test Code **
	//****************************
	
	//Unit Test Data for Symbol
	vector<int> *testVector = new vector<int>( );
	testVector->push_back( 1 );
	testVector->push_back( 2 );
	testVector->push_back( 3 );
	testVector->push_back( 4 );
	testVector->push_back( 1 );
	int st = 1, ic = 1, le = 0, fp = 5;
	
	//unit Test - Symbol
	Symbol *versionOne = new Symbol( );
	versionOne->setSymbolType( st );
	versionOne->setIntercharGap( ic );
	versionOne->setLeadingElement( le );
	versionOne->setForcedPosition( fp );
	versionOne->setEncodedData( *testVector );
	
	cout << "Unit Test - Symbol" << endl;
	cout << "Symbol Type: " << versionOne->getSymbolType( ) << endl;
	cout << "Leading Element: " << versionOne->getLeadingElement( ) << endl;
	cout << "IC Gap: " << versionOne->getIntercharGap( ) << endl;
	cout << "Force Position: " << versionOne->getForcePostion( ) << endl;
	cout << "Encoded Data: " << versionOne->getEncodedData( ) << endl;
	
	for ( int ii = 0; ii < testVector->size( ); ii++ ) 
	{
		cout << "test: " << testVector->at( ii ) << " actual: " << versionOne->getEncodedData( )->at( ii )	<< endl;
	}
	
	delete testVector;
	delete versionOne;
	//End Unit Test - Symbol
	
	
	
	//****************************
	//** RapidXML Test Code ******
	//****************************
	
	//Test code for RapidXML parser
	ifstream xmlfile ( "xml_test.xml", ios::in );
	
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
		cout << xmltoparse.length( ) << endl;			//DEBUG check string length
	}
	
	char * cxml = new char [ xmltoparse.size( ) + 1 ];	//copy string into cstring
	strcpy ( cxml, xmltoparse.c_str( ) );
	
	xml_document< > parsed_xml;
	parsed_xml.parse< 0 >( cxml );
	
	xml_node< > *node = NULL;
	node = parsed_xml.first_node( )->first_node()->next_sibling()->first_node();
	
	while ( node->next_sibling( ) != 0 ) 
	{
		cout << node->name( );
		xml_node< > *datanode = node->first_node();
		while (datanode != 0) 
		{
			cout << " : " << datanode->value();
			datanode = datanode->next_sibling();
		}
		cout << endl;
		node = node->next_sibling( );
	}
	
	node = parsed_xml.first_node( )->first_node()->next_sibling()->next_sibling()->first_node();
	
	while ( node->next_sibling( ) != 0 ) 
	{
		cout << node->name( );
		xml_node< > *datanode = node->first_node();
		while (datanode != 0) 
		{
			cout << " : " << datanode->value();
			datanode = datanode->next_sibling();
		}
		cout << endl;
		node = node->next_sibling( );
	}
	//End XML Test code
	
    return 0;
}

