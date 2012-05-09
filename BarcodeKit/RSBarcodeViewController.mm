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
	
	CGFloat selfwidth = self.view.frame.size.width;
	int totalModules = ( data_accumulator + nondata_accumulator );
	[self setDatamoduleCount:data_accumulator];
	[self setNondatamoduleCount:nondata_accumulator];
	[self setTotalmoduleCount:totalModules];
	CGFloat findX = selfwidth / totalModules;
	self.xWidth = findX;
	
	//create an RSSymbol for each Symbol
	NSPoint insertionPoint = NSMakePoint( 0, 0);
	for ( int ii = 0; ii < testDeque.size( ); ii++ ) 
	{	
		//Work out the width for each one, loop through vector
		NSMutableArray *symbolPattern = [[NSMutableArray alloc] init];
		CGFloat width_accum = 0;
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
		
		CGFloat newY, newHeight;
		if ( ( BC == kRSEAN13 || BC == kRSEAN8 || BC == kRSUPCA || BC == kRSUPCE || BC == kRSInterleaved ) && ( type == kRSData || type == kRSCheckChar || type == kRSQuietZone ) ) //The human readable ones...
		{
			newY = self.view.frame.size.height * 0.15;
			newHeight = self.view.frame.size.height *0.85;
			[self humanReadableText: BC];
		} 
		else 
		{	
			newY = 0;
			newHeight = self.view.frame.size.height;
		}
		
		//create an RSSymbol for each Symbol
		RSSymbol *aSymbol = [[RSSymbol alloc] initWithFrame:NSMakeRect( insertionPoint.x, newY, width_accum * _xWidth, newHeight ) andData:[NSArray arrayWithArray:symbolPattern] startingWith:se andX:_xWidth ofType:type];
		
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

- (void) humanReadableText:( enum kRSBarcode ) BC
{
	CGFloat localWidth = self.view.frame.size.width;
	CGFloat localHeight = self.view.frame.size.height;
	
	NSString *contentString = [NSString stringWithCString:barcode->completedDataString.c_str( ) encoding:NSASCIIStringEncoding];
	
	NSTextView *labelOne = [[NSTextView alloc] init];
	NSTextView *labelTwo = [[NSTextView alloc] init];
	NSTextView *labelThree = [[NSTextView alloc] init];
	NSTextView *labelFour = [[NSTextView alloc] init];
	
	[labelOne setBackgroundColor:[NSColor clearColor]];
	[labelOne setAlignment:NSCenterTextAlignment];
	[labelOne setEditable:NO];
	
	[labelTwo setBackgroundColor:[NSColor clearColor]];
	[labelTwo setAlignment:NSCenterTextAlignment];
	[labelTwo setEditable:NO];
	
	[labelThree setBackgroundColor:[NSColor clearColor]];
	[labelThree setAlignment:NSCenterTextAlignment];
	[labelThree setEditable:NO];
	
	[labelFour setBackgroundColor:[NSColor clearColor]];
	[labelFour setAlignment:NSCenterTextAlignment];
	[labelFour setEditable:NO];
	
	switch ( BC ) 
	{
		case kRSEAN13:
			[labelOne setString:[contentString substringWithRange:NSMakeRange(0, 1)]];
			[labelOne setFrame:NSMakeRect( 0, -(localHeight * 0.05), localWidth * 0.08, localHeight * 0.15 )];
			[labelOne setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelOne setNeedsDisplay:YES];
			[self.view addSubview:labelOne];
			
			[labelTwo setString:[contentString substringWithRange:NSMakeRange(0, 6)]];
			[labelTwo setFrame:NSMakeRect( localWidth * 0.13, -(localHeight * 0.05), localWidth * 0.35, localHeight * 0.15 )];
			[labelTwo setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelTwo setNeedsDisplay:YES];
			[self.view addSubview:labelTwo];
			
			[labelThree setString:[contentString substringWithRange:NSMakeRange(6, 6)]];
			[labelThree setFrame:NSMakeRect( localWidth * 0.53, -(localHeight * 0.05), localWidth * 0.35, localHeight * 0.15 )];
			[labelThree setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelThree setNeedsDisplay:YES];
			[self.view addSubview:labelThree];
			
			[labelFour setString:[ contentString substringWithRange:NSMakeRange(12, 1)]];
			[labelFour setFrame:NSMakeRect( localWidth * 0.91, -(localHeight * 0.05), localWidth * 0.1, localHeight * 0.15 )];
			[labelFour setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelFour setNeedsDisplay:YES];
			[self.view addSubview:labelFour];
			break;
		case kRSEAN8:
			[labelOne setString:@"<"];
			[labelOne setFrame:NSMakeRect( 0, -(localHeight * 0.05), localWidth * 0.08, localHeight * 0.15 )];
			[labelOne setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelOne setNeedsDisplay:YES];
			[self.view addSubview:labelOne];
			
			[labelTwo setString:[contentString substringWithRange:NSMakeRange(0, 4)]];
			[labelTwo setFrame:NSMakeRect( localWidth * 0.13, -(localHeight * 0.05), localWidth * 0.33, localHeight * 0.15 )];
			[labelTwo setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelTwo setNeedsDisplay:YES];
			[self.view addSubview:labelTwo];
			
			[labelThree setString:[contentString substringWithRange:NSMakeRange(4, 4)]];
			[labelThree setFrame:NSMakeRect( localWidth * 0.53, -(localHeight * 0.05), localWidth * 0.33, localHeight * 0.15 )];
			[labelThree setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelThree setNeedsDisplay:YES];
			[self.view addSubview:labelThree];
			
			[labelFour setString:@">"];
			[labelFour setFrame:NSMakeRect( localWidth * 0.91, -(localHeight * 0.05), localWidth * 0.1, localHeight * 0.15 )];
			[labelFour setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelFour setNeedsDisplay:YES];
			[self.view addSubview:labelFour];
			break;
		case kRSUPCA:
			[labelOne setString:[contentString substringWithRange:NSMakeRange(0, 1)]];
			[labelOne setFrame:NSMakeRect( 0, -(localHeight * 0.05), localWidth * 0.08, localHeight * 0.15 )];
			[labelOne setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelOne setNeedsDisplay:YES];
			[self.view addSubview:labelOne];
			
			[labelTwo setString:[contentString substringWithRange:NSMakeRange(1, 5)]];
			[labelTwo setFrame:NSMakeRect( localWidth * 0.13, -(localHeight * 0.05), localWidth * 0.35, localHeight * 0.15 )];
			[labelTwo setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelTwo setNeedsDisplay:YES];
			[self.view addSubview:labelTwo];
			
			[labelThree setString:[contentString substringWithRange:NSMakeRange(6, 5)]];
			[labelThree setFrame:NSMakeRect( localWidth * 0.53, -(localHeight * 0.05), localWidth * 0.35, localHeight * 0.15 )];
			[labelThree setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelThree setNeedsDisplay:YES];
			[self.view addSubview:labelThree];
			
			[labelFour setString:[ contentString substringWithRange:NSMakeRange(11, 1)]];
			[labelFour setFrame:NSMakeRect( localWidth * 0.91, -(localHeight * 0.05), localWidth * 0.1, localHeight * 0.15 )];
			[labelFour setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelFour setNeedsDisplay:YES];
			[self.view addSubview:labelFour];
			break;
		case kRSUPCE:
			[labelOne setString:@"0"];
			[labelOne setFrame:NSMakeRect( 0, -(localHeight * 0.05), localWidth * 0.08, localHeight * 0.15 )];
			[labelOne setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelOne setNeedsDisplay:YES];
			[self.view addSubview:labelOne];
			
			[labelTwo setString:[ contentString substringWithRange:NSMakeRange(0, 6)]];
			[labelTwo setFrame:NSMakeRect( localWidth * 0.13, -(localHeight * 0.05), localWidth * 0.7, localHeight * 0.15 )];
			[labelTwo setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelTwo setNeedsDisplay:YES];
			[self.view addSubview:labelTwo];
			
			[labelFour setString:[ contentString substringWithRange:NSMakeRange(6, 1)]];
			[labelFour setFrame:NSMakeRect( localWidth * 0.91, -(localHeight * 0.05), localWidth * 0.1, localHeight * 0.15 )];
			[labelFour setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelFour setNeedsDisplay:YES];
			[self.view addSubview:labelFour];
			break;
		case kRSInterleaved:
			[labelTwo setString:contentString];
			[labelTwo setFrame:NSMakeRect( localWidth * 0.13, -(localHeight * 0.05), localWidth * 0.7, localHeight * 0.15 )];
			[labelTwo setFont:[NSFont fontWithName:@"OCRB" size:localHeight * 0.13]];
			[labelTwo setNeedsDisplay:YES];
			[self.view addSubview:labelTwo];
			break;
			
		default:
			break;
	}
}

- (void) loadView
{
	
}



@end
