//
//  Code39.h
//  BarcodeKit
//	Header file for Code 39 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Code39_h
#define Code39_h

#import "BaseBarcode.h"
#import "Symbol.h"
#import <vector>
#import <deque> 
#import <string> 

using namespace std;

class Code39 : BaseBarcode
{
	public:
	Code39( );
	~Code39( );
	bool verifyContent ( const string *content );
	void encodeSymbol ( const string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( );
};

#endif
