//
//  RSBarcodeViewController.mm
//  MacBarcode
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#import "RSBarcodeViewController.h"
#import "RSSymbol.h"
#include "BaseBarcode.h"
#include "Codabar.h"
#include "Code39.h"
#include "Interleaved2of5.h"
#include "Code128.h"
#include "EAN13.h"
#include "EAN8.h"
#include "UPCA.h"
#include "UPCE.h"
#include "Symbol.h"
#include <deque>
#include <iostream>

@interface RSBarcodeViewController ()

@end

@implementation RSBarcodeViewController

@synthesize xWidth = _xWidth;
@synthesize datamoduleCount = _datamoduleCount;
@synthesize nondatamoduleCount = _nondatamoduleCount;
@synthesize totalmoduleCount = _totalmoduleCount;
@synthesize dataString = _dataString;
@synthesize theView = _theView;

- (id)initWithType:( enum kRSBarcode ) BC andData:(NSString *)barcodeData atPosition:(NSRect)rect
{
	//**call to superclass init**
    self = [super initWithNibName:nil bundle:nil];
    if (self)
	{
		[self setDataString:barcodeData];
		_theView = [[NSView alloc] initWithFrame:rect];
		[self setView:_theView];
		NSLog(@"Frame: %f, %f, %f, %f", self.view.frame.origin.x, self.view.frame.origin.y, self.view.frame.size.width, self.view.frame.size.height);
    }
	
	
	//**create the correct subtype**
	string *cplusplus_datastring = new string( [_dataString cStringUsingEncoding:NSASCIIStringEncoding] );
	switch ( BC ) 
	{
		case kRSCodabar:
			barcode = new Codabar( cplusplus_datastring );
			break;
		case kRSCode39:
			barcode = new Code39( cplusplus_datastring );
			break;
		case kRSInterleaved:
			barcode = new Interleaved2of5( cplusplus_datastring );
			break;
		case kRSCode128:
			barcode = new Code128( cplusplus_datastring );
			break;
		case kRSEAN13:
			barcode = new EAN13( cplusplus_datastring );
			break;
		case kRSEAN8:
			barcode = new EAN8( cplusplus_datastring );
			break;
		case kRSUPCA:
			barcode = new UPCA( cplusplus_datastring );
			break;
		case kRSUPCE:
			barcode = new UPCE( cplusplus_datastring );
			break;
		default:
			break;
	}
	
	
	deque< Symbol* > testDeque = barcode->getEncodedSymbols( );
	NSMutableArray *modulesPerSymbol = [[NSMutableArray alloc] init];
	int nondata_accumulator = 0, data_accumulator = 0, icgap = 0, local_accum = 0;
	for ( int gg = 0; gg < testDeque.size( ); gg++ ) 
	{
		vector< int > *pattern;
		pattern = testDeque.at( gg )->getEncodedData( );
		switch ( testDeque.at( gg )->getSymbolType( ) ) 
		{
			case 0: //add up all the element widths for data
				icgap = testDeque.at( gg )->getIntercharGap( );
				data_accumulator += icgap;
				local_accum = 0;
				for ( int hh = 0; hh < pattern->size( ); hh++ ) 
				{
					int result = pattern->at( hh );
					local_accum += result;
					data_accumulator = data_accumulator + result;
				}
				[modulesPerSymbol addObject:[NSNumber numberWithInt:local_accum]];
			break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5: //add up all the element widths for nondata
				icgap = testDeque.at( gg )->getIntercharGap( );
				nondata_accumulator += icgap;
				local_accum = 0;
				for ( int hh = 0; hh < pattern->size( ); hh++ ) 
				{
					int result = pattern->at( hh );
					local_accum += result;
					nondata_accumulator += result;
				}
				[modulesPerSymbol addObject:[NSNumber numberWithInt:local_accum]];
				break;
			default:
				break;
		}
		
	}
	
	int selfwidth = ( int )self.view.frame.size.width;
	int totalModules = ( data_accumulator + nondata_accumulator );
	[self setDatamoduleCount:data_accumulator];
	[self setNondatamoduleCount:nondata_accumulator];
	[self setTotalmoduleCount:totalModules];
	int findX = selfwidth / totalModules;
	self.xWidth = findX;
	
	//create an RSSymbol for each Symbol
	
	
	
	NSPoint insertionPoint = NSMakePoint( 0, 0);
	for ( int ii = 0; ii < testDeque.size( ); ii++ ) 
	{	
		//Work out the width for each one, loop through vector
		NSMutableArray *symbolPattern = [[NSMutableArray alloc] init];
		int width_accum = 0;
		for ( int jj = 0; jj < testDeque.at( ii )->getEncodedData( )->size( ); jj++ ) 
		{
			width_accum += testDeque.at( ii )->getEncodedData( )->at( jj );
			[symbolPattern addObject:[NSNumber numberWithInt:testDeque.at( ii )->getEncodedData( )->at( jj )]];
		}
		width_accum += testDeque.at( ii )->getIntercharGap( );
		
		kRSStarter se;
		switch ( testDeque.at( ii )->getLeadingElement( ) ) 
		{
			case 0:
				se = kRSSpace;
				break;
			case 1:
				se = kRSBar;
			default:
				break;
		}
		
		kRSType type;
		switch ( testDeque.at( ii )->getSymbolType( ) ) 
		{
			case 0:
				type = kRSData;
				break;
			case 1:
				type = kRSCheckChar;
				break;
			case 2:
				type = kRSQuietZone;
				break;
			case 3:
				type = kRSGuardPattern;
				break;
			case 4:
				type = kRSStartStop;
				break;
			case 5:
				type= kRSNonData;
				break;
			default:
				break;
		}
		
		//create an RSSymbol for each Symbol
		RSSymbol *aSymbol = [[RSSymbol alloc] initWithFrame:NSMakeRect( insertionPoint.x, insertionPoint.y, (CGFloat)width_accum * _xWidth, self.view.frame.size.height ) andData:[NSArray arrayWithArray:symbolPattern] startingWith:se andX:_xWidth ofType:type];
		
		//Add them into self.view
		[self.view addSubview:aSymbol];
		//increment insertionPoint by symbol width
		insertionPoint.x += width_accum * _xWidth;
		
		//NSLog( @"%@ ", symbolPattern );
		
		symbolPattern = nil;
		[symbolPattern release];
	}
	
	
    delete cplusplus_datastring;
    return self;
}

- (void) loadView
{
	
}



@end
