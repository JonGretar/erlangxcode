//
//  ErlCCommandOutputParser.h
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 24.9.2008.
//

#import "XCPOutputParsing.h"

@interface EXCommandOutputParserErlc : XCBuildCommandOutputParser
{
	NSString*	_lastFilePath;
	unsigned	_lastLineNum;
	NSString*	_lastCharRange;
	unsigned	_lastMessageType;
}

- (id)initWithNextOutputStream:(XCOutputStream*)nextOutputStream;
- (void)writeBytes:(const char *)data length:(unsigned int)length;


@end