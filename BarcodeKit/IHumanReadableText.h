//
//  IHumanReadableText.h
//  BarcodeKit
//
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_IHumanReadableText_h
#define BarcodeKit_IHumanReadableText_h

#include <string>

using namespace std;

class IHumanReadableText
{
	public:
	virtual void setHumanReadableText( string text ) = 0;
	virtual string getHumanReadableText( ) = 0;
	virtual void encodeHumanReadableText( ) = 0;
};

#endif
