//
//  Codabar.h
//  BarcodeKit
//	Header file for Codabar Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Codabar_h
#define Codabar_h

#include "BaseBarcode.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

class Codabar : public BaseBarcode
{
	public:
	Codabar( );
	Codabar( std::string *data );
	~Codabar( );
	bool verifyContent ( const std::string *content );
	void encodeSymbol ( const std::string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( const std::string *data );

	private:
	std::string filename;
	rapidxml::xml_document< > parsed_xml;
	std::vector< int >* stringToVector( std::string aString );
};

#endif