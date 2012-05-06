//
//  IGuardPatterns.h
//  BarcodeKit
//	//Pure Abstract base Class, interface to give ivars and methods decs for GPs
//  Created by Robert Stearn on 06.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#ifndef BarcodeKit_IGuardPatterns_h
#define BarcodeKit_IGuardPatterns_h

#include <vector> 
#include <string>

using namespace std;

class IGuardPatterns
{
	public:
	virtual void setGuardPatterns( string left, string centre, string right ) = 0;
	virtual vector< string > getGuardPatterns( ) = 0;
	virtual void encodeGuardPatterns( ) = 0;
};

#endif
