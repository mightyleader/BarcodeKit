//
//  BaseBarcode.h
//  BarcodeKit
//	Abstract Base Class for Barcode class heirarchy
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

using namespace std;

class BaseBarcode
{
	protected:
	//Build and Destroy
	BaseBarcode( );	//override
	~BaseBarcode( ); 
	
	//Accessors
	vector<int> getQuietzoneWidths( );
	deque<Symbol*> getEncodedSymbols( );
	int getCheckcharModulus( );
	int getDataLength( );
	
	void setQuietzoneWidths( int left, int right, int upper, int lower );
	void addEncodedSymbol( Symbol* symbol );
	void addEncodedSymbol( Symbol* symbol, int position );
	void setCheckcharModulus( int modulus );
	void setDataLength( int length );
					 
	//Methods
	virtual bool verifyData ( const string *data );
	virtual bool verifyLength ( const int length );
	virtual bool verifyContent ( const string *content ) = 0; //override
	
	virtual void encodeSymbol ( const string *data ) = 0; //override
	virtual void encodeStartStop ( ) = 0;
	virtual void encodeQuietZones ( ) = 0;
	virtual void encodeCheckCharacter ( ) = 0;
	
	Symbol* createSymbol( int st, int ic, int le, int fp, vector< int > *aVector );
	char* getXMLToParse( string *fileTitle );
	vector<string> returnDOMValues( rapidxml::xml_node< > *node );

	private:
	//iVars
	vector<int> quietzoneWidths;
	deque<Symbol*> encodedSymbols;
	int checkcharModulus;
	int dataLength;	
};
					 
#endif