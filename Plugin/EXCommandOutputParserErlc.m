//
//  ErlCCommandOutputParser.m
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 24.9.2008.
//

#import "EXCommandOutputParserErlc.h"
#import "XCPSupport.h"


TSRegularExpression* __regex_warning = nil;
TSRegularExpression* __regex_error = nil;

@implementation EXCommandOutputParserErlc

+ (void)initialize
{
	__regex_warning = [[TSRegularExpression alloc] initWithExpressionString:@"(.*):(.*): (Warning:.*)"];
	__regex_error = [[TSRegularExpression alloc] initWithExpressionString:@"(.*):(.*): (.*)"];
}


- (id)initWithNextOutputStream:(XCOutputStream*)nextOutputStream
{
	if((self = [super initWithNextOutputStream:nextOutputStream]) == nil) return nil;
	
	return self;
}

- (void)writeBytes:(const char*)data length:(unsigned)length
{
	NSString* line = [[[NSString alloc] initWithBytes:data length:length encoding:NSASCIIStringEncoding] autorelease];
	NSArray* subexpressions;
	
	// First we check for warnings
	if( nil != (subexpressions = [__regex_warning subexpressionsForString:line]))
	{
		NSString* FilePath = [subexpressions objectAtIndex:1];
		NSString* LineNumber = [subexpressions objectAtIndex:2];
		NSString* ErrorText = [subexpressions objectAtIndex:3];
		
		id SelfDelegate = [self delegate];
		[SelfDelegate parser:self 
		  foundMessageOfType:2
					   title:[ErrorText UTF8String]
			   forFileAtPath:[FilePath UTF8String]
				  lineNumber:[LineNumber intValue]];
	}
	// Any other messages are errors.
	else if( nil != (subexpressions = [__regex_error subexpressionsForString:line]))
	{
		NSString* FilePath = [subexpressions objectAtIndex:1];
		NSString* LineNumber = [subexpressions objectAtIndex:2];
		NSString* ErrorText = [subexpressions objectAtIndex:3];
		
		id SelfDelegate = [self delegate];
		[SelfDelegate parser:self 
		  foundMessageOfType:1 
					   title:[ErrorText UTF8String]
			   forFileAtPath:[FilePath UTF8String]
				  lineNumber:[LineNumber intValue]];
	}
	
	
	[super writeBytes:data length:length];
}

@end
