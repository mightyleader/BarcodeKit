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

#pragma mark --Accessor Methods--

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
	
	switch ( position ) {
		case 0:
			this->encodingpatternData.insert( encodingpatternData.begin( ), pattern );
			break;
		//case limit:
			
		default:
			break;
	}
	this->encodingpatternData.insert(encodingpatternData.begin(), pattern);
}

void BaseBarcode::addEncodedPatternNonData( Symbol* pattern, int position )
{
	
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
	if ( this->dataLength == length ) 
	{
		return true;
	}
	cerr << "Data string length does not pass verification" << endl;
	return false;
}

bool BaseBarcode::verifyContent ( const string *content )
{
	cerr << "Data cannot be encoded by into a barcode-compatible format" << endl;
	return false;
}
