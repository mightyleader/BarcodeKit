//
//  RSBarcodeViewController.h
//  MacBarcode
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RSSymbol.h"
#include "BaseBarcode.h"

enum kRSBarcode 
{
	kRSCodabar		= 0,
	kRSCode39		= 1,
	kRSInterleaved	= 2,
	kRSCode128		= 3,
	kRSEAN13		= 4,
	kRSEAN8			= 5,
	kRSUPCA			= 6,
	kRSUPCE			= 7
};


@interface RSBarcodeViewController : NSViewController
{
	BaseBarcode *barcode;
}

@property ( nonatomic )	CGFloat	xWidth;
@property ( nonatomic )	int	datamoduleCount;
@property ( nonatomic )	int	nondatamoduleCount;
@property ( nonatomic )	int	totalmoduleCount;
@property ( nonatomic, retain )	NSString *dataString;
@property ( nonatomic, retain ) NSView *theView;

- (id)initWithType:( enum kRSBarcode ) BC andData:(NSString *)barcodeData atPosition:(NSRect)rect;
- (void) humanReadableText:( enum kRSBarcode ) BC;


@end
