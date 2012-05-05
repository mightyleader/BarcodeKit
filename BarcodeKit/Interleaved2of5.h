//
//  Interleaved2of5.h
//  BarcodeKit
//	Header file for Interleaved2of5 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Interleaved2of5_h
#define Interleaved2of5_h

#import "BaseBarcode.h"
#import "Symbol.h"
#import "rapidxml.hpp"
#import <vector>
#import <deque> 
#import <string> 

using namespace std;
using namespace rapidxml;

class Interleaved2of5 : public BaseBarcode
{
	public:
	Interleaved2of5( string *data );
	~Interleaved2of5( );
	bool verifyContent ( const string *content );
	void encodeCheckCharacter ( const string *data );
	void encodeSymbol ( const string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	
	
	private:
	string filename;
	xml_document< > parsed_xml;
	vector< int >* stringToVector( string aString );
};

#endif
