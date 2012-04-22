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
	BaseBarcode( );
	~BaseBarcode( );
					 
	private:
	//Methods
	virtual bool verifyData ( const string *data );
	virtual bool verifyLength ( const int length );
	virtual bool verifyContent ( const string *content );
	
	virtual void encodeSymbol ( const string *data ) = 0;
	virtual void encodeStartStop ( ) = 0;
	virtual void encodeQuietZones ( ) = 0;
	virtual void encodeCheckCharacter ( ) = 0;
	
	//Accessors
	vector<Symbol*> getEncodingpatternData( );
	vector<Symbol*> getEncodingPatternNondata( );
	vector<int> getQuietzoneWidths( );
	deque<Symbol*> getEncodedSymbols( );
	int getCheckcharModulus( );
	int getDataLength( );
	
	void addEncodedPatternData( Symbol* pattern );							//adds to end
	void addEncodedPatternNonData( Symbol* pattern );						// ditto
	void addEncodedPatternData( Symbol* pattern, int position );			//adds at specified index
	void addEncodedPatternNonData( Symbol* pattern, int position );			// ditto
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
};
					 
#endif