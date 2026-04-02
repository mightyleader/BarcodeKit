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

class UPCE : public BaseEANUPC, public IGuardPatterns
{
public:
	//**constructors**
	UPCE( std::string *data );
	~UPCE( );
	void encodeSymbol( const std::string *data );
	void encodeQuietZones( );
	void encodeGuardPatterns( );
	void setGuardPatterns( std::string left, std::string centre, std::string right );
	//void encodeCheckCharacter( const std::string *data );
	std::vector< std::string > getGuardPatterns( );
	std::vector< int >* stringToVector( std::string aString );
	bool verifyContent ( const std::string *content );

	//**format specific methods**
	std::string* zeroSuppression( const std::string *data );
	bool isZeroSuppresible( const std::string *data );
	int getZSPattern( );
	void setZSPattern( int pattern );

	std::string filename;
	std::string checkFilename;
	std::vector< std::string > guardPatterns;
	rapidxml::xml_document< > parsed_xml;
	rapidxml::xml_document< > parity_xml;
	int zsPattern;
};

#endif
