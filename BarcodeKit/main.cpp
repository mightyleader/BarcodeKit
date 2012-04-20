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
	/*
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
	*/
	
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
	
	xml_node< > *node;
	xml_node< > *anothernode;
	
	node = parsed_xml.first_node("barcode");
	cout << "Name of my first node is: " << node->name( ) << "\n";
	
	for ( anothernode = node->first_node( ); 
		  anothernode; 
		  anothernode = anothernode->first_node( ) ) 
	{
		cout << "Name of next child node is: " << anothernode->name( ) << "\n";
		if ( anothernode->first_node( ) == 0 ) 
		{
			anothernode = anothernode->next_sibling( );
			cout << "Name of next sibling node is: " << anothernode->name( ) << "\n";
			for ( xml_attribute< > *attr = anothernode->first_attribute( );
				 attr; attr = attr->next_attribute( ) )
			{
				cout << "Node has attribute " << attr->name( ) << " ";
				cout << "with value " << attr->value( ) << "\n";
			}
			
		}
	}
	
	

	
	//	for ( xml_attribute< > *attr = node->first_attribute( );
	//		 attr; attr = attr->next_attribute( ) )
	//	{
	//		cout << "Node has attribute " << attr->name( ) << " ";
	//		cout << "with value " << attr->value( ) << "\n";
	//	}
	//	
	//	xml_node< > *nextnode = node->first_node();
	//	cout << "Name of my next node is: " << nextnode->name( ) << "\n";
	
	for ( xml_attribute< > *attr = anothernode->first_attribute( );
		 attr; attr = attr->next_attribute( ) )
		{
			cout << "Node has attribute " << attr->name( ) << " ";
			cout << "with value " << attr->value( ) << "\n";
		}	
	

	
	//End XML Test code
	
    return 0;
}

