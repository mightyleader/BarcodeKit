//
//  Base128.h
//  BarcodeKit
//	Header for base class of Code128 and Code 16k
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Base128_h
#define Base128_h

#include "BaseBarcode.h"
#include "Symbol.h"
#include <vector>
#include <deque> 
#include <string> 
#include "rapidxml.hpp"

using namespace std;
using namespace rapidxml;

class Base128 : public BaseBarcode
{
	protected:
	Base128( );
	~Base128( );
	virtual void encodeSymbol ( const string *data );
	virtual int returnCheckCharASCII(  ) = 0;
};

#endif