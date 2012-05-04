//
//  Interleaved2of5.h
//  BarcodeKit
//	Header file for Interleaved2of5 Class
//  Created by Robert Stearn on 22.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef Interleaved2of5_h
#define Interleaved2of5_h

#import "BaseBarcode.h"
#import "Symbol.h"
#import <vector>
#import <deque> 
#import <string> 

using namespace std;

class Interleaved2of5 : BaseBarcode
{

	public:
	Interleaved2of5( );
	~Interleaved2of5( );
	bool verifyContent ( const string *content );
	void encodeSymbol ( const string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( );
	
	private:
	int[] validASCII = {48,49,50,51,52,53,54,55,56,57\0};
	
};

#endif
