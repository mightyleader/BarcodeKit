//
//  Base128.cpp
//  BarcodeKit
//	Definitions for Base128 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string>
#include "Base128.h"
#include "Symbol.h"
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

#pragma mark --Con/Destructors--

Base128::Base128( string *data )
{
	//parse xml
	
	//iterate through DOM
	
	//add entries into data structure
	
	ifstream xmlfile ( "xml_test.xml", ios::in );		//setup file for input...
	vector<string> xmlcontent;							//...and the vars we'll use 
	string xmlentry;
	string xmltoparse;
	
	if ( xmlfile.is_open( ) )							//open the file
	{
		while ( getline( xmlfile, xmlentry ) )			//get the data
		{
			xmlcontent.push_back( xmlentry + "\n" );	//add data to vector
		}
		xmlfile.close( );								//close the file
		
		for ( int i = 0; i < xmlcontent.size( ); i++ )	//iterate through vector 
		{
			xmltoparse += xmlcontent[ i ];				//add it to the string
		}
	}
	char * cxml = new char [ xmltoparse.size( ) + 1 ];	
	strcpy ( cxml, xmltoparse.c_str( ) );				//convert string into cstring req'd by API
	
	xml_document< > parsed_xml;							//setup DOM object...
	parsed_xml.parse< 0 >( cxml );						//...pass cstring to parser to parse into DOM object
	
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
	
}


Base128::~Base128( )
{
	
}


#pragma mark --Methods--

void Base128::encodeSymbol ( const string *data )
{
	//for each char in string get ascii value
	//pull pattern from data structure
	//create symbol for each
	//add to the data structure
	
	//q's handling sets, 
}