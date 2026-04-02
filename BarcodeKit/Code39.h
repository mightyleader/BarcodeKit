//
//  Code39.h
//  BarcodeKit
//	Header file for Code 39 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Code39_h
#define Code39_h

#include "BaseBarcode.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

class Code39 : public BaseBarcode
{
	public:
	Code39( std::string *data );
	~Code39( );
	bool verifyContent ( const std::string *content );
	void encodeSymbol ( const std::string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( const std::string *data );

	private:
	std::string filename;
	rapidxml::xml_document< > parsed_xml;
	std::vector< int >* stringToVector( std::string aString );
	int checksumIntForChar( int aChar );
	char checksumCharForInt( int anInt );
};

#endif