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

class Codabar : BaseBarcode
{

	public:
	Codabar( );
	~Codabar( );
	bool verifyContent ( const string *content );
	void encodeSymbol ( const string *data );
	void encodeStartStop ( );
	void encodeQuietZones ( );
	void encodeCheckCharacter ( );
	
		
	private:
	int[] validASCII = {36,43,45,46,47,48,49,50,51,52,53,54,55,56,57,58,65,66,67,68,\0};
	
};

#endif
