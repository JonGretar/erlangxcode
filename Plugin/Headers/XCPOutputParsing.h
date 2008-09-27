/*
	XCPOutputParsing.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
	
	Output parsering
*/

#import <Foundation/Foundation.h>

typedef enum {
	XCP_ErrorMessage	= 1,
	XCP_WarningMessage	= 2,
} XCPMessageType;

@protocol XCBuildCommandOutputParserDelegates
- (void)parserFoundEndOfMostRecentInclusion:(id)parser;
- (void)parserFoundEndOfAllInclusions:(id)parser;
#if XCODE_VERSION < 22
- (void)parser:(id)parser foundInclusionMessage:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
- (void)parser:(id)parser foundNoticeMessage:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
- (void)parser:(id)parser foundLocationSpecifierMessage:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
- (void)parser:(id)parser foundWarningMessage:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
- (void)parser:(id)parser foundErrorMessage:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
#else
- (void)parser:(id)parser foundMessageOfType:(XCPMessageType)type title:(const char*)message forFileAtPath:(const char*)path lineNumber:(unsigned)line;
- (void)parser:(id)parser subcommand:(id)fp12 didStartInSubslot:(unsigned int)fp16;
- (void)parser:(id)parser subcommand:(id)fp12 didEmitLineOfOutputInSubslot:(unsigned int)fp16 bytes:(const char *)fp20 length:(unsigned int)fp24;
- (void)parser:(id)parser subcommand:(id)fp12 didEmitMessageInSubslot:(unsigned int)fp16 type:(unsigned int)fp20 title:(const char *)fp24 forFileAtPath:(const char *)fp28 lineNumber:(unsigned int)fp32;
- (void)parser:(id)parser subcommand:(id)fp12 didPopMostRecentInclusionMessageInSubslot:(unsigned int)fp16;
- (void)parser:(id)parser subcommand:(id)fp12 didPopAllInclusionMessagesInSubslot:(unsigned int)fp16;
- (void)parser:(id)parser subcommand:(id)fp12 didEndInSubslot:(unsigned int)fp16 resultCode:(int)fp20;
#endif
@end

@protocol XCOutputStreams <NSObject>
- (void)writeBytes:(const char*)data length:(unsigned)length;
- (void)flush;
- (void)close;
@end

@interface XCOutputStream : NSObject <XCOutputStreams>
- (void)writeBytes:(const char*)data length:(unsigned)length;
- (void)flush;
- (void)close;
- (void)writeData:(NSData*)data;
@end

@interface XCFilterOutputStream : XCOutputStream
{
    id _nextOutputStream;
}
- (id)initWithNextOutputStream:(XCOutputStream*)nextOutputStream;
- (id)init;
- (void)dealloc;
- (XCOutputStream*)nextOutputStream;
- (void)setNextOutputStream:(XCOutputStream*)nextOutputStream;
- (XCOutputStream*)lastOutputStream;
- (void)writeBytes:(const char*)data length:(unsigned)length;
- (void)flush;
- (void)close;
@end

@interface XCBuildCommandOutputParser : XCFilterOutputStream
{
    id _delegate;
}
- (id)initWithNextOutputStream:(XCOutputStream*)nextOutputStream;
- (id)delegate;
- (void)setDelegate:(id)delegate;
- (void)writeBytes:(const char*)data length:(unsigned)length;
@end
