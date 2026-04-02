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

class Code128 : public Base128
{
	public:
	Code128( std::string *data );
	~Code128( );
	int getSet( char first );
	bool verifyContent ( const std::string *content );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( const std::string *data );
	int returnCheckCharASCII(  );

	private:
	std::string filename;
	rapidxml::xml_document< > parsed_xml;
	std::vector< int >* stringToVector( std::string aString );

};

#endif
