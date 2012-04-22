//
//  BaseBarcode.cpp
//  BarcodeKit
//
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
	
}

void BaseBarcode::addEncodedPatternNonData( Symbol* pattern )
{
	
}

void addEncodedPatternData( Symbol* pattern, int position )
{
	
}

void addEncodedPatternNonData( Symbol* pattern, int position )
{
	
}

void BaseBarcode::setQuietzoneWidths( int left, int right, int upper, int lower )
{
	
}

void BaseBarcode::addEncodedSymbol( Symbol* symbol )
{
	
}

void BaseBarcode::setCheckcharModulus( int modulus )
{
	
}

void BaseBarcode::setDataLength( int length )
{
	this->dataLength = this->encodedSymbols.size();
}

#pragma mark --Private internal methods--

bool BaseBarcode::verifyData ( const string *data )
{
	if ( this->verifyLength( data->length( ) ) && this->verifyContent( data ) ) 
	{
		return true;
	}
	return false;
}

bool BaseBarcode::verifyLength ( const int length )
{
	if ( this->dataLength == length ) 
	{
		return true;
	}
	return false;
}

bool BaseBarcode::verifyContent ( const string *content )
{
	return false;
}
