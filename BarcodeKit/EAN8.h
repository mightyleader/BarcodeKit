//
//  EAN8.h
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_EAN8_h
#define BarcodeKit_EAN8_h

#include "BaseEANUPC.h"
#include "IGuardPatterns.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

class EAN8 : public BaseEANUPC, public IGuardPatterns
{
public:
	EAN8( std::string *data );
	~EAN8( );
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
};

#endif
