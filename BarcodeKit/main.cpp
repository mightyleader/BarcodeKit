//
//  main.cpp
//  BarcodeKit
//
//  Created by Robert Stearn on 09.04.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Symbol.h"

using namespace std;

int main(int argc, const char * argv[])
{	
	//Unit Test Data for Symbol
	vector<int> *testVector = new vector<int>();
	testVector->push_back(1);
	testVector->push_back(2);
	testVector->push_back(3);
	testVector->push_back(4);
	testVector->push_back(1);
	int st = 1, ic = 1, le = 0, fp = 5;
	
	//unit Test - Symbol
	Symbol *versionOne = new Symbol( );
	versionOne->setSymbolType( st );
	versionOne->setIntercharGap( ic );
	versionOne->setLeadingElement( le );
	versionOne->setForcedPosition( fp );
	versionOne->setEncodedData( *testVector );
	
	cout << "Unit Test - Symbol" << endl;
	cout << "Symbol Type: " << versionOne->getSymbolType( ) << endl;
	cout << "Leading Element: " << versionOne->getLeadingElement( ) << endl;
	cout << "IC Gap: " << versionOne->getIntercharGap( ) << endl;
	cout << "Force Position: " << versionOne->getForcePostion( ) << endl;
	cout << "Encoded Data: " << versionOne->getEncodedData( ) << endl;
	
	for ( int ii = 0; ii < testVector->size( ); ii++ ) 
	{
		cout << "test: " << testVector->at( ii ) << " actual: " << versionOne->getEncodedData( )->at( ii )	<< endl;
	}
	
	delete testVector;
	delete versionOne;
	//End Unit Test - Symbol
	
    return 0;
}

