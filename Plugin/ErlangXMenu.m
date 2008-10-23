//
//  ErlangXMenu.m
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 23.10.2008.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "ErlangXMenu.h"


@implementation ErlangXMenu


-(IBAction) visitWebsite: (id)sender
{
	NSURL *someURL;
	if ([sender tag] == 0) {
		someURL = [NSURL URLWithString:@"http://medevyoujane.com/erlangx/"];
	}
	else {
		someURL = [NSURL URLWithString:@"http://erlang.org/"];
	}
	[[NSWorkspace sharedWorkspace] openURL:someURL];
	[someURL release];
}

@end
