//
//  RSSymbol.m
//  MacBarcode
//
//  Created by Robert Stearn on 07.05.12.
//  Copyright (c) 2012 Cocoadelica. All rights reserved.
//

#import "RSSymbol.h"

@implementation RSSymbol

@synthesize pattern = _pattern, startingElement = _startingElement, xWidth = _xWidth, drawPoint = _drawPoint, theType = _theType;

- (id)initWithFrame:( NSRect )frame andData:( NSArray* )data startingWith:(enum kRSStarter) starter andX:( CGFloat ) xW ofType:(enum kRSType) type
{
    self = [super initWithFrame:frame];
    if ( self ) 
	{
        [self setXWidth:xW];
		[self setStartingElement:starter];
		_pattern = [[NSArray alloc] initWithArray:data];
		[self setDrawPoint:NSMakePoint( 0, 0 )];
		[self setTheType:type];
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    for ( int rr = 0; rr < _pattern.count; rr++ ) 
	{
		CGFloat element_width = _xWidth * [[_pattern objectAtIndex:rr] intValue];
		NSRect element = NSMakeRect( _drawPoint.x, _drawPoint.y, element_width, self.frame.size.height );
		int loop_modulus = rr % 2;
		if ( _theType == 2 ) 
		{
			[[NSColor clearColor] set];
		} 
		else 
		{
			switch ( _startingElement ) 
			{
				case 1:
					if ( loop_modulus == 0 ) 
					{
						[[NSColor clearColor] set];
					}
					if ( loop_modulus == 1) 
					{
						[[NSColor blackColor] set];
					}
					break;
				case 0:
					if ( loop_modulus == 0 ) 
					{
						[[NSColor blackColor] set];
					}
					if ( loop_modulus == 1) 
					{
						[[NSColor clearColor] set];
					}
					break;
				default:
					break;
			}
		}		
		NSRectFill( element );
		_drawPoint.x += element_width;
	}
}

@end
