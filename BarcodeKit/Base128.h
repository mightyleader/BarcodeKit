//
//  Base128.h
//  BarcodeKit
//	Header for base class of Code128 and Code 16k
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Base128_h
#define Base128_h

#import "BaseBarcode.h"
#import "Symbol.h"
#import <vector>
#import <deque> 
#import <string> 

using namespace std;

class Base128 : BaseBarcode
{
	protected:
	Base128( string *data );
	~Base128( );
	virtual void encodeSymbol ( const string *data );
};

#endif
