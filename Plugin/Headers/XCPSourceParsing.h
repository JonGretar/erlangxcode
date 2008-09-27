/*
	XCPSourceParsing.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
	
	Language definition and source code parsing
*/

#import <Foundation/Foundation.h>

@interface PBXLexicalRules : NSObject
{
	NSMutableCharacterSet*	_commentStartChars;
	NSMutableCharacterSet*	_endCommentStartChars;
	NSMutableCharacterSet*	_singleLineCommentStartChars;
	NSMutableCharacterSet*	_stringStartChars;
	NSMutableCharacterSet*	_endStringStartChars;
	NSMutableCharacterSet*	_charStartChars;
	NSMutableCharacterSet*	_endCharStartChars;
	NSMutableCharacterSet*	_identifierStartChars;
	NSMutableCharacterSet*	_identifierChars;
	NSCharacterSet*			_nonIdentifierCharacters;
	NSMutableCharacterSet*	_numericStartChars;
	NSMutableCharacterSet*	_numericChars;
	NSMutableCharacterSet*	_endOfLineChars;
	NSCharacterSet*			_whitespaceChars;
	NSCharacterSet*			_nonWhitespaceChars;
	PBXSourceTokens*		_keywords;
	PBXSourceTokens*		_altKeywords;
	PBXSourceTokens*		_docCommentKeywords;
	PBXSourceTokens*		_preprocessorKeywords;
	NSMutableArray*			_stringDelimiters;
	NSMutableArray*			_commentDelimiters;
	NSMutableArray*			_singleLineComment;
	NSMutableArray*			_characterDelimiters;
	NSString*				_docComment;
	unsigned short			_docCommentKeywordStart;
	unsigned short			_preprocessorKeywordStart;
	unsigned short			_escapeCharacter;
	NSCharacterSet*			_linkStartChars;
	NSCharacterSet*			_linkPrefixChars;
	NSCharacterSet*			_urlLocationChars;
	NSCharacterSet*			_domainNameStartChars;
	NSCharacterSet*			_domainNameChars;
	NSString*				_urlSchemeDelimiter;
	NSString*				_mailLocalNameDelimiter;
	BOOL					_caseSensitive;
	BOOL					_unicodeSymbols;
	BOOL					_indexedSymbols;
	BOOL					_commentsCanBeNested;
	BOOL					_fortranStyleComments;
}
- (id)init;
- (id)initWithDictionary:(id)fp8;
- (void)addDictionary:(id)fp8;
- (BOOL)isCommentStartChar:(unsigned short)fp8;
- (BOOL)isEndCommentStartChar:(unsigned short)fp8;
- (BOOL)isSingleLineCommentStartChar:(unsigned short)fp8;
- (BOOL)isStringStartChar:(unsigned short)fp8;
- (BOOL)isEndStringStartChar:(unsigned short)fp8;
- (BOOL)isCharStartChar:(unsigned short)fp8;
- (BOOL)isEndCharStartChar:(unsigned short)fp8;
- (BOOL)isIdentifierStartChar:(unsigned short)fp8;
- (BOOL)isIdentifierChar:(unsigned short)fp8;
- (BOOL)isNumericStartChar:(unsigned short)fp8;
- (BOOL)isNumericChar:(unsigned short)fp8;
- (BOOL)isEndOfLineChar:(unsigned short)fp8;
- (BOOL)isWhitespaceChar:(unsigned short)fp8;
- (BOOL)isLinkStartChar:(unsigned short)fp8;
- (BOOL)isDomainNameStartChar:(unsigned short)fp8;
- (id)nonIdentifierCharacterSet;
- (id)nonWhitespaceCharacterSet;
- (BOOL)isKeyword:(id)fp8;
- (BOOL)isAltKeyword:(id)fp8;
- (BOOL)isDocCommentKeyword:(id)fp8;
- (BOOL)isPreprocessorKeyword:(id)fp8;
- (id)keywords;
- (id)altKeywords;
- (id)docCommentKeywords;
- (id)preprocessorKeywords;
- (id)stringDelimiters;
- (id)commentDelimiters;
- (id)singleLineComment;
- (id)characterDelimiters;
- (id)docComment;
- (unsigned short)escapeCharacter;
- (unsigned short)preprocessorKeywordStart;
- (unsigned short)docCommentKeywordStart;
- (id)urlSchemeDelimiter;
- (id)mailLocalNameDelimiter;
- (id)linkPrefixChars;
- (id)urlLocationChars;
- (id)domainNameChars;
- (BOOL)caseSensitive;
- (BOOL)unicodeSymbols;
- (BOOL)indexedSymbols;
- (BOOL)commentsCanBeNested;
- (BOOL)fortranStyleComments;
- (int)tokenForString:(id)fp8;
- (BOOL)isNumber:(id)fp8 withRange:(NSRange*)fp12;
@end

@interface PBXSourceLexer : NSObject
{
	PBXLexicalRules* _rules;
	NSRange			_tokenRange;
	NSString*		_tokenString;
	id				_delegate;
	BOOL			_ignoreNewLines;
	BOOL			fortranStyleComments;
	char*			characterMap;
	XCAttributeRun*	_tokenRun;
}
- (id)initWithLexicalRules:(id)fp8;
- (void)dealloc;
- (void)finalize;
- (void)setDelegate:(id)fp8;
- (void)setString:(id)fp8 range:(NSRange)fp12;
- (void)scanSubRange:(NSRange)fp8 startingInState:(int)fp16;
- (id)rules;
- (void)setIgnoreNewLines:(BOOL)fp8;
- (void)skipWhitespace;
- (unsigned short)nextCharWithoutSkippingWhitespace;
- (unsigned short)nextChar;
- (unsigned short)peekChar;
- (unsigned short)peekCharWithoutSkippingWhitespace;
- (unsigned)peekCharacterInSet:(id)fp8;
- (unsigned)curLocation;
- (void)setLocation:(unsigned int)fp8;
- (void)incLocation;
- (void)decLocation;
- (unsigned)length;
- (void)parseDocCommentFromLoc:(unsigned)fp8 matchIndex:(int)fp12;
- (void)scanForLinksInRange:(NSRange)fp8;
- (void)skipMultiLineCommentFromLoc:(unsigned)fp8 matchIndex:(int)fp12;
- (void)buildCharacterMap;
- (int)nextToken;
- (int)nextToken:(BOOL)fp8;
- (void)stringWasEdited:(NSRange*)fp8 replacementLength:(int)fp12;
- (int)cachedTokenTypeAtLocation:(unsigned)fp8 tokenRange:(NSRange*)fp12;
- (int)peekToken;
- (id)tokenString;
- (void)setTokenStringToRange:(NSRange)fp8;
- (id)stringForRange:(NSRange)fp8;
- (NSRange)tokenRange;
- (unsigned short)skipToCharacter:(unsigned short)fp8 orCharacter:(unsigned short)fp12 withEscape:(BOOL)fp16;
- (void)skipToCharacter:(unsigned short)fp8 withEscape:(BOOL)fp12;
- (void)skipToString:(id)fp8 withEscape:(BOOL)fp12;
- (void)skipToEndOfLineWithEscape:(BOOL)fp8;
- (BOOL)inputMatchesString:(id)fp8;
- (BOOL)inputIsInSet:(id)fp8;
- (void)skipToEndDelimeter:(unsigned short)fp8 withStart:(unsigned short)fp12;
@end

@interface PBXSourceLexer (PBXPrivate)
- (void)gotCharacterForRange:(NSRange)range;
- (void)gotStringForRange:(NSRange)range;
- (void)gotNumberForRange:(NSRange)range;
- (void)gotCommentForRange:(NSRange)range;
- (void)gotMultilineCommentForRange:(NSRange)range;
- (void)gotDocCommentForRange:(NSRange)range;
- (void)gotDocCommentKeywordForRange:(NSRange)range;
- (void)gotKeywordForRange:(NSRange)range;
- (void)gotAltKeywordForRange:(NSRange)range;
- (void)gotIdentifierForRange:(NSRange)range;
- (void)gotPreprocessorForRange:(NSRange)range;
- (void)gotURLForRange:(NSRange)range;
- (void)gotMailAddressForRange:(NSRange)range;
@end

@interface PBXSourceScanner : NSObject
{
	PBXSourceLexer* _lexer;
}
- (id)initWithLanguageSpecification:(id)fp8;
- (void)dealloc;
- (void)finalize;
- (id)lexer;
- (void)initSourceLexerForSpecification:(id)fp8;
- (void)initInterestingSymbols;
- (id)parseString:(id)fp8;
- (id)parse;
@end

@protocol PBXScannerItem <NSObject>
- (id)name;
- (id)nameWithIndent;
- (int)type;
- (int)compareWithScannerItem:(id)fp8;
@end

@interface PBXSourceScannerItem : NSObject <PBXScannerItem>
{
	NSString*		name;
	NSMutableArray*	children;
	int				type;
	PBXSourceScannerItem* parent;
	NSRange			nameRange;
	NSRange			range;
	int				nestingLevel;
	int				indentLevel;
}
- (id)initWithName:(id)fp8 type:(int)fp12;
- (void)dealloc;
- (void)finalize;
- (id)description;
- (id)name;
- (id)nameWithIndent;
- (void)setName:(id)fp8;
- (void)addChild:(id)fp8;
- (id)childAtIndex:(int)fp8;
- (int)numberOfChildren;
- (int)type;
- (void)setType:(int)fp8;
- (BOOL)isDeclaration;
- (id)parent;
- (void)setParent:(id)fp8;
- (NSRange)nameRange;
- (void)setNameRange:(NSRange)fp8;
- (NSRange)range;
- (void)setRange:(NSRange)fp8;
- (int)nestingLevel;
- (void)setNestingLevel:(int)fp8;
- (int)indentLevel;
- (void)setIndentLevel:(int)fp8;
- (int)compareWithScannerItem:(id)fp8;
@end

@interface PBXSourceTokens : NSObject
{
	NSMutableSet*	_tokens;
	BOOL			_caseSensitive;
}
+ (int)_tokenForString:(id)fp8;
+ (int)addTokenForString:(id)fp8;
- (id)initWithArrayOfStrings:(id)fp8 caseSensitive:(BOOL)fp12;
- (void)dealloc;
- (void)finalize;
- (void)addArrayOfStrings:(id)fp8;
- (BOOL)containsToken:(id)fp8;
- (int)tokenForString:(id)fp8;
- (id)allTokens;
@end

/*
	@interface PBXCSourceScanner : PBXSourceScanner
		@interface PBXNQCSourceScanner : PBXCSourceScanner
		@interface PBXObjCPPSourceScanner : PBXCSourceScanner
		@interface PBXCPPSourceScanner : PBXCSourceScanner
		@interface PBXObjCSourceScanner : PBXCSourceScanner
	@interface PBXJamSourceScanner : PBXSourceScanner
	@interface PBXJavaScriptSourceScanner : PBXSourceScanner
	@interface PBXJavaSourceScanner : PBXSourceScanner
	@interface PBXLabelSourceScanner : PBXSourceScanner
	@interface PBXPerlSourceScanner : PBXSourceScanner
	@interface PBXPythonSourceScanner : PBXSourceScanner
	@interface PBXRubySourceScanner : PBXSourceScanner
*/
