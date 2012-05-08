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

using namespace std;

class BaseEANUPC : public BaseBarcode, public IGuardPatterns
{
	public:
	BaseEANUPC( );
	~BaseEANUPC( );
	bool verifyContent ( const string *content );
	virtual void encodeSymbol ( const string *data );
	virtual void encodeQuietZones ( );
	virtual void encodeStartStop( );
	virtual void encodeCheckCharacter ( const string *data );
	virtual void setGuardPatterns( string left, string centre, string right ) = 0;
	virtual vector< string > getGuardPatterns( ) = 0;
	virtual void encodeGuardPatterns( ) = 0;
	
	string completedDataString;
};

#endif