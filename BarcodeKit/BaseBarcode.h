//
//  BaseBarcode.h
//  BarcodeKit
//	Pure Virtual Abstract Base Class for Barcode class heirarchy
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BaseBarcode_h
#define BaseBarcode_h

#include "Symbol.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class BaseBarcode
{
	public:
	//Build and Destroy
	BaseBarcode( ) = 0;
	BaseBarcode( const string *data ) = 0;
	~BaseBarcode( ) = 0;
					 
	private:
	//Methods
	bool verifyData ( const string *data );
	bool verifyLength ( const int length );
	bool verifyContent ( const string *content );
	
	void encodeSymbol ( const string *data ) = 0;
	void encodeStartStop ( ) = 0;
	void encodeQuietZones ( ) = 0;
	void encodeCheckCharacter ( ) = 0;
	
	//Accessors
	vector<Symbol*> encodingpatternData( );
	vector<Symbol*> encodingPatternNondata( );
	vector<int> quietzoneWidths( );
	deque<Symbol*> encodedSymbols( );
	int checkcharModulus( );
	int dataLength( );
	
	void addEncodedPatternData( Symbol* pattern );
	void addEncodedPatternNonData( Symbol* pattern );
	void setQuietzoneWidths( int left, int right, int upper, int lower );
	void addEncodedSymbol( Symbol* symbol );
	void setCheckcharModulus( int modulus );
	void setDataLength( int length );
	
	//iVars
	vector<Symbol*> encodingpatternData;
	vector<Symbol*> encodingPatternNondata;
	vector<int> quietzoneWidths;
	deque<Symbol*> encodedSymbols;
	int checkcharModulus;
	int dataLength;	
}
					 
					 
#endif