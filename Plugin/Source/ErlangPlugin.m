//
//  ErlangPlugin.m
//  Erlang
//
//  Created by J�n Gr�tar Borg?�rsson on 20.9.2008.
//

#import "ErlangPlugin.h"

@implementation ErlangPlugin 

+ (void)pluginDidLoad:(NSBundle *)bundle
{
  NSLog(@"ErlangPlugin loaded - %@", bundle);
  
//  No need for this at the moment. 
//  if (![NSBundle loadNibNamed:@"ErlangPlugin" owner:self])
//  {
//    NSLog(@"Warning! Could not load ErlangPlugin nib file.\n");
//  }
  
}

@end
