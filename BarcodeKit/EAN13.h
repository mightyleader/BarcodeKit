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

class EAN13 : public BaseEANUPC, public IGuardPatterns
{
public:
	EAN13( std::string *data );
	~EAN13( );
	void encodeSymbol( const std::string *data );
	void encodeQuietZones( );
	void encodeGuardPatterns( );
	void setGuardPatterns( std::string left, std::string centre, std::string right );
	std::vector< std::string > getGuardPatterns( );
	std::vector< int >* stringToVector( std::string aString );

	std::string filename;
	std::string parityFilename;
	std::vector< std::string > guardPatterns;
	rapidxml::xml_document< > parsed_xml;
	rapidxml::xml_document< > parity_xml;
};

#endif

