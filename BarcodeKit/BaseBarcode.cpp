//
//  BaseBarcode.cpp
//  BarcodeKit
//	Pure Virtual Abstract Base Class for Barcode class heirarchy
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include "BaseBarcode.h"
#include "Symbol.h"
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <fstream>
#include <sstream>
#include "rapidxml.hpp"

using namespace std;

// MARK: -- Con/Destructors --

BaseBarcode::BaseBarcode( )
{
	//empty
}

BaseBarcode::~BaseBarcode( )
{
	//empty
}

// MARK: -- Accessor Methods --

// MARK: -- Getters --

vector<int> BaseBarcode::getQuietzoneWidths( )
{
	return this->quietzoneWidths;
}


deque<Symbol*> BaseBarcode::getEncodedSymbols( )
{
	return this->encodedSymbols;
}


int BaseBarcode::getCheckCharModulus( )
{
	return checkCharModulus;
}


int BaseBarcode::getDataLength( )
{
	return dataLength;
}


// MARK: -- Setters --

void BaseBarcode::setQuietzoneWidths( int left, int right, int upper, int lower )
{
	this->quietzoneWidths.clear( );
	quietzoneWidths.push_back( left );
	quietzoneWidths.push_back( right );
	quietzoneWidths.push_back( upper );
	quietzoneWidths.push_back( lower );

}


void BaseBarcode::addEncodedSymbol( Symbol* symbol )
{
	this->encodedSymbols.push_back( symbol );
}


void BaseBarcode::addEncodedSymbol( Symbol* symbol, int position )
{
	if ( position == 0 )
	{
		this->encodedSymbols.insert( this->encodedSymbols.begin( ), symbol );
	}
	else
	{
		this->encodedSymbols.insert( this->encodedSymbols.begin( ) + position, symbol );
	}
}


void BaseBarcode::setCheckCharModulus( int modulus )
{
	this->checkCharModulus = modulus;
}


void BaseBarcode::setDataLength( int length )
{
	this->dataLength = length;
}


// MARK: -- Private internal methods --

bool BaseBarcode::verifyData ( const string *data )
{
	if ( this->verifyLength( data->length( ) ) && this->verifyContent( data ) )
	{
		return true;
	}
	cerr << "Data does not pass verification tests" << endl;
	return false;
}


bool BaseBarcode::verifyLength ( const int length )
{
	if ( this->dataLength == -1 )
	{
		return true; //if there is no length limit
	}
	if ( this->dataLength == length )
	{
		return true; //if the requested length meets the comparison
	}
	cerr << "Data string length does not pass verification" << endl; //else throw error
	return false;
}

// MARK: -- Helper Methods --

Symbol* BaseBarcode::createSymbol( int st, int ic, int le, int fp, vector<int> *aVector ) //make a new symbol with passed values
{
	Symbol *shinyNewSymbol = new Symbol( );
	shinyNewSymbol->setSymbolType( st );
	shinyNewSymbol->setIntercharGap( ic );
	shinyNewSymbol->setLeadingElement( le );
	shinyNewSymbol->setForcedPosition( fp );
	shinyNewSymbol->setEncodedData( *aVector );
	return shinyNewSymbol;
}


char* BaseBarcode::getXMLToParse( string *fileTitle ) //Safely get the XML file into a c_string
{
	char *ft = new char[ fileTitle->length( ) + 1 ];
	strcpy( ft, fileTitle->c_str( ) );
	ifstream xmlfile ( ft, ios::in );
	delete[] ft;	// free the temporary filename buffer

	vector<string> xmlcontent;
	string xmlentry;
	string xmltoparse;

	if ( xmlfile.is_open( ) )						//open the file
	{
		while ( getline( xmlfile, xmlentry ) )		//get the data
		{
			xmlcontent.push_back( xmlentry + "\n" );	//add data to vector
		}
		xmlfile.close( );

		for ( int i = 0; i < xmlcontent.size( ); i++ )	//iterate through vector into string
		{
			xmltoparse += xmlcontent[ i ];
		}
	}

	char *cxml = new char[ xmltoparse.size( ) + 1 ];	//copy string into cstring
	strcpy( cxml, xmltoparse.c_str( ) );

	return cxml;
}


vector<string> BaseBarcode::returnDOMValues( rapidxml::xml_node< > *node ) //Return contents of a single named or unnamed node in the DOM
{
	vector<string> returnValues;	// local variable — no heap allocation needed
	rapidxml::xml_node< > *datanode = node->first_node( );
	while ( datanode != 0 )
	{
		rapidxml::xml_node< > *childnode = datanode->first_node( );
		while ( childnode != 0 )
		{
			string aValue = childnode->value( );
			returnValues.push_back( aValue );
			childnode = childnode->next_sibling( );
		}
		datanode = datanode->next_sibling( );
	}
	node = node->next_sibling( );

	return returnValues;
}
