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
	
	private:
	int[] validASCII = {32,36,42,43,45,46,47,48,49,50,51,52,53,54,55,56,
		57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
		86,87,88,89,90\0};
	
};

#endif
