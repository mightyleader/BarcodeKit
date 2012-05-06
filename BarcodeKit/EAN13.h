//
//  EAN13.h
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_EAN13_h
#define BarcodeKit_EAN13_h

#include "BaseEANUPC.h"
#include "IGuardPatterns.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

using namespace std;
using namespace rapidxml;

class EAN13 : public BaseEANUPC, public IGuardPatterns
{
public:
	EAN13( string *data );
	~EAN13( );
	void encodeSymbol( const string *data );
	void encodeQuietZones( );
	void encodeGuardPatterns( );
	void setGuardPatterns( string left, string centre, string right );
	vector< string > getGuardPatterns( );
	vector< int >* stringToVector( string aString );
	
	string filename;
	string parityFilename;
	vector< string >guardPatterns;
	xml_document< > parsed_xml;
	xml_document< > parity_xml;
};

#endif

