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

#pragma mark --Con/Destructors--

BaseBarcode::BaseBarcode( )
{
	//empty
}

BaseBarcode::~BaseBarcode( )
{
	//empty
}

#pragma mark --Accessor Methods--

#pragma mark --Getters--

vector<Symbol*> BaseBarcode::getEncodingpatternData( )
{
	return this->encodingpatternData;
}


vector<Symbol*> BaseBarcode::getEncodingPatternNondata( )
{
	return this->encodingPatternNondata;
}


vector<int> BaseBarcode::getQuietzoneWidths( )
{
	return this->quietzoneWidths;
}


deque<Symbol*> BaseBarcode::getEncodedSymbols( )
{
	return this->encodedSymbols;
}


int BaseBarcode::getCheckcharModulus( )
{
	return checkcharModulus;
}


int BaseBarcode::getDataLength( )
{
	return dataLength;
}


#pragma mark --Setters--

void BaseBarcode::addEncodedPatternData( Symbol* pattern )
{
	this->encodingpatternData.push_back( pattern );
}


void BaseBarcode::addEncodedPatternNonData( Symbol* pattern )
{
	this->encodingPatternNondata.push_back( pattern );
}


void BaseBarcode::addEncodedPatternData( Symbol* pattern, int position )
{
	if ( position == 0 ) 
	{
		this->encodingpatternData.insert( this->encodingpatternData.begin( ), pattern );
	} 
	else 
	{
		this->encodingpatternData.insert( this->encodingpatternData.begin( ) + position, pattern );
	}
}


void BaseBarcode::addEncodedPatternNonData( Symbol* pattern, int position )
{
	if ( position == 0 ) 
	{
		this->encodingPatternNondata.insert( this->encodingPatternNondata.begin( ), pattern );
	} 
	else 
	{
		this->encodingPatternNondata.insert( this->encodingPatternNondata.begin( ) + position, pattern );
	} 
}


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


void BaseBarcode::setCheckcharModulus( int modulus )
{
	this->checkcharModulus = modulus;
}


void BaseBarcode::setDataLength( int length )
{
	this->dataLength = length;
}


#pragma mark --Private internal methods--

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
		return true; //if the requested length meets the comaprison
	}
	cerr << "Data string length does not pass verification" << endl; //else throw error
	return false;
}


bool BaseBarcode::verifyContent ( const string *content )
{
	for ( int i = 0; i < content->length( ); i++ ) 
	{
		int asciiOfChar = (int)content->at( i );
		
		if ( this->encodingpatternData.at( asciiOfChar ) == NULL ) 
		{
			cerr << "Data cannot be encoded by into a barcode-compatible format" << endl;
			return false;
		}
	}
	
	return true;
}
