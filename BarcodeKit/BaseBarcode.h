//
//  BaseBarcode.h
//  BarcodeKit
//	Abstract Base Class for Barcode class hierarchy
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BaseBarcode_h
#define BaseBarcode_h

#include "Symbol.h"
#include <string>
#include <vector>
#include <deque>
#include "rapidxml.hpp"

class BaseBarcode
{
	public:
	//Accessors
	std::vector< int > getQuietzoneWidths( );
	std::deque< Symbol* > getEncodedSymbols( );
	int getCheckCharModulus( );
	int getDataLength( );

	protected:
	//Build and Destroy
	BaseBarcode( );
	~BaseBarcode( );

	//Accessors
	void setQuietzoneWidths( int left, int right, int upper, int lower );
	void addEncodedSymbol( Symbol* symbol );
	void addEncodedSymbol( Symbol* symbol, int position );
	void setCheckCharModulus( int modulus );
	void setDataLength( int length );

	//Methods
	virtual bool verifyData ( const std::string *data );
	virtual bool verifyLength ( const int length );
	virtual bool verifyContent ( const std::string *content ) = 0;

	virtual void encodeSymbol ( const std::string *data ) = 0;
	virtual void encodeStartStop ( ) = 0;
	virtual void encodeQuietZones ( ) = 0;
	virtual void encodeCheckCharacter ( const std::string *data ) = 0;

	Symbol* createSymbol( int st, int ic, int le, int fp, std::vector< int > *aVector );
	char* getXMLToParse( std::string *fileTitle );
	std::vector<std::string> returnDOMValues( rapidxml::xml_node< > *node );

	//iVars
	std::vector< int > quietzoneWidths;
	std::deque< Symbol* > encodedSymbols;
	int checkCharModulus;
	int dataLength;
	std::string completedDataString;
};

#endif
