//
//  UPCE.h
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_UPCE_h
#define BarcodeKit_UPCE_h

#include "BaseEANUPC.h"
#include "IGuardPatterns.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

using namespace std;
using namespace rapidxml;

class UPCE : public BaseEANUPC, public IGuardPatterns
{
public:
	//**consructors**
	UPCE( string *data );
	~UPCE( );
	void encodeSymbol( const string *data );
	void encodeQuietZones( );
	void encodeGuardPatterns( );
	void setGuardPatterns( string left, string centre, string right );
	//void encodeCheckCharacter( const string *data );
	vector< string > getGuardPatterns( );
	vector< int >* stringToVector( string aString );
	bool verifyContent ( const string *content );
	
	//**format specific methods**
	string* zeroSuppression( const string *data );
	bool isZeroSuppresible( const string *data );
	int getZSPattern( );
	void setZSPattern( int pattern );
	
	string filename;
	string checkFilename;
	vector< string >guardPatterns;
	xml_document< > parsed_xml;
	xml_document< > parity_xml;
	int zsPattern;
};

#endif
