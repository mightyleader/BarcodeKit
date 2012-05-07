//
//  Code128.h
//  BarcodeKit
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_Code128_h
#define BarcodeKit_Code128_h

#include "Base128.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

using namespace std;
using namespace rapidxml;

class Code128 : public Base128
{
	public:
	Code128( string *data );
	~Code128( );
	int getSet( char first );
	bool verifyContent ( const string *content );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( const string *data );
	int returnCheckCharASCII(  );
	
	private:
	string filename;
	xml_document< > parsed_xml;
	vector< int >* stringToVector( string aString );
	
};

#endif
