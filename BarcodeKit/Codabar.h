//
//  Codabar.h
//  BarcodeKit
//	Header file for Codabar Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Codabar_h
#define Codabar_h

#import "BaseBarcode.h"
#import "Symbol.h"
#import <vector>
#import <deque> 
#import <string> 

using namespace std;

class Codabar : public BaseBarcode
{
	public:
	Codabar( );
	Codabar( string *data );
	~Codabar( );
	bool verifyContent ( const string *content );
	void encodeSymbol ( const string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( const string *data );
};

#endif
