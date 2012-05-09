//
//  RSSymbol.h
//  MacBarcode
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#import <Cocoa/Cocoa.h>

enum kRSStarter 
{
	kRSBar		= 0,
	kRSSpace	= 1
};

enum kRSType
{
	kRSData			= 0,
	kRSCheckChar	= 1,
	kRSQuietZone	= 2,
	kRSGuardPattern = 3,
	kRSStartStop	= 4,
	kRSNonData		= 5
};

@interface RSSymbol : NSView
@property ( nonatomic, retain ) NSArray *pattern;
@property ( nonatomic ) int startingElement;
@property ( nonatomic ) int xWidth;
@property ( nonatomic ) NSPoint drawPoint;
@property ( nonatomic ) int theType;

- (id)initWithFrame:( NSRect )frame andData:( NSArray* )data startingWith:(enum kRSStarter) starter andX:( CGFloat ) xW ofType:( enum kRSType ) type;

@end

