//
//  BaseEANUPC.h
//  BarcodeKit
//	Header for base class of EAN-13, EAN-8, UPC-A and UPC-E
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BaseEANUPC_h
#define BaseEANUPC_h

#include "BaseBarcode.h"
#include "IGuardPatterns.h"
#include "Symbol.h"
#include "rapidxml.hpp"
#include <vector>
#include <deque> 
#include <string> 

class BaseEANUPC : public BaseBarcode, public IGuardPatterns
{
	public:
	BaseEANUPC( );
	~BaseEANUPC( );
	bool verifyContent ( const std::string *content );
	virtual void encodeSymbol ( const std::string *data );
	virtual void encodeQuietZones ( );
	virtual void encodeStartStop( );
	virtual void encodeCheckCharacter ( const std::string *data );
	virtual void setGuardPatterns( std::string left, std::string centre, std::string right ) = 0;
	virtual std::vector< std::string > getGuardPatterns( ) = 0;
	virtual void encodeGuardPatterns( ) = 0;
};

#endif