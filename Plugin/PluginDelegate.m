//
//  PluginDelegate.m
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 23.10.2008.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "PluginDelegate.h"


@implementation PluginDelegate


-(void)awakeFromNib 
{
	[[NSApp mainMenu] addItem:myMenu];
}

@end
