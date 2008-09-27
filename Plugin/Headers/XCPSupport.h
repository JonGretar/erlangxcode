/*
	XCPSupport.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
	
	Development Tool Support Framework.
*/

#import <Foundation/Foundation.h>

/*
	Regular expression search.
	Does not support more than 20 subexpressions.
	Only return informations about the first occurrence.
*/
@interface TSRegularExpression : NSObject <NSCopying, NSCoding>
{
	NSString*	_expressionString;
	NSString*	_lastMatch;
	NSRange		_lastSubexpressionRanges[20];
	void*		_compiledExpression;
	BOOL		_ignoreCase;
}
+ (BOOL)validExpressionString:(NSString*)regex;
+ (id)regularExpressionWithString:(NSString*)regex ignoreCase:(BOOL)ignore;
+ (id)regularExpressionWithString:(NSString*)regex;
- (id)initWithExpressionString:(NSString*)regex ignoreCase:(BOOL)ignore;
- (id)initWithExpressionString:(NSString*)regex;
- (NSString*)expressionString;
- (BOOL)matchesString:(NSString*)string;
- (NSRange)rangeForSubexpressionAtIndex:(unsigned)fp8 inString:(NSString*)string;
- (NSString*)substringForSubexpressionAtIndex:(unsigned)fp8 inString:(NSString*)string;
- (NSArray*)subexpressionsForString:(NSString*)string;
@end

/**/
@interface NSString (TSStringAdditions)
+ (unsigned)TSDefaultCStringEncoding;
+ (void)setTSDefaultCStringEncoding:(unsigned)fp8;
+ (BOOL)isFileUnicode:(id)fp8 fileData:(id)fp12;
+ (BOOL)isFileUTF8WithBOM:(id)fp8 fileData:(id)fp12;
- (id)arrayByParsingAsCommandLineArguments;
- (id)arrayByParsingAsStringList;
- (void)testMacroExpansion;
- (id)namesOfExpandableVariables;
- (id)TS_stringByExpandingVariables:(id)fp8 inRange:(NSRange)fp12 options:(unsigned)fp20;
- (id)TS_stringByExpandingVariables:(id)fp8 options:(unsigned)fp12;
- (id)TS_stringByExpandingEnvironmentVariables;
- (id)stringByDeletingLeadingWhitespace;
- (id)stringByDeletingTrailingWhitespace;
- (id)stringByDeletingAllWhitespace;
- (id)stringByAbbreviatingWithEllipsisInMiddleToLength:(unsigned)fp8;
- (BOOL)isLegalCIdentifier;
- (id)stringByManglingToLegalCIdentifier;
- (id)stringByEscapingForXML;
- (id)stringByUnescapingFromXML;
- (id)initWithContentsOfFile:(id)fp8 defaultCStringEncoding:(unsigned)fp12 getStringEncoding:(unsigned*)fp16;
- (id)initWithUnicodeOrMacOSRomanContentsOfFile:(id)fp8 getStringEncoding:(unsigned*)fp12;
- (id)initWithPotentiallyMalformedUTF8Bytes:(const char*)fp8 length:(unsigned)fp12 stopAtTrailingIncompleteUTF8Sequence:(BOOL)fp16 getUsedLength:(unsigned*)fp20 getNumberOfMalformedSequences:(unsigned*)fp24;
- (void)getLineStartOffsets:(unsigned**)fp8 count:(unsigned*)fp12;
- (NSRange)rangeNotHavingLiteralPrefixAndSuffixInCommonWithRange:(NSRange)fp8 ofString:(id)fp16;
- (BOOL)writeUsingFileSystemEncodingToFile:(id)fp8 atomically:(BOOL)fp12;
@end

@interface NSMutableString (PBXTSStringAdditions)
- (void)appendSubstringWithRange:(NSRange)range ofString:(NSString*)string;
- (void)deleteCharactersFromSet:(NSCharacterSet*)set atIndex:(unsigned)index options:(unsigned)options;
- (void)deleteLeadingWhitespace;
- (void)deleteAllWhitespace;
- (void)deleteTrailingWhitespace;
- (void)deleteAllCharactersInSet:(NSCharacterSet*)set;
@end

@interface NSCharacterSet (TSStringAdditions)
+ (id)isspaceCharacterSet;
@end

@interface NSUserDefaults (TSUserDefaultsExtra)
- (BOOL)boolForKey:(NSString*)key withDefaultValue:(BOOL)defaultValue;
@end

@interface NSInvocation (TSFoundationExtra)
+ (id)invocationWithTarget:(id)target selector:(SEL)select object:(id)object;
@end

@interface NSMutableAttributedString (TSFoundationExtra)
- (void)appendString:(id)string attributes:(id)attributes;
@end

@interface NSDictionary (TSFoundationExtra)
- (NSDictionary*)dictionaryByAddingEntriesFromDictionary:(NSDictionary*)dict;
- (NSDictionary*)dictionaryByRecursivelyElidingEmptyStringValuesForKeysInSet:(id)set;
- (NSString*)stringByConcatenatingEntriesAsLinesOfSimpleAssignments;
- (NSDictionary*)inverseDictionary;
@end

@interface NSMutableArray (TSFoundationExtra)
- (void)addObjectIfAbsent:(id)object;
- (void)addObjectsFromArrayIfAbsent:(id)object;
- (void)correctlyRemoveObjectsFromIndices:(unsigned*)indices numIndices:(unsigned)num;
- (void)moveObjectsFromIndices:(unsigned*)indices numIndices:(unsigned)num toIndex:(unsigned)index;
@end

@interface NSArray (TSFoundationExtra)
+ (NSArray*)arrayWithArraysOrObjects:(id)arg;
- (NSArray*)initWithArraysOrObjects:(id)arg;
- (void)makeObjectsPerformSelector:(SEL)selector withObject:(id)object withObject:(id)obj2;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector withObject:(id)obj2 withObject:(id)obj3 inReverseOrder:(BOOL)reverse;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector withObject:(id)obj2 withObject:(id)obj3;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector withObject:(id)obj2 inReverseOrder:(BOOL)reverse;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector withObject:(id)obj2;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector inReverseOrder:(BOOL)reverse;
- (void)processObjectsUsingObject:(id)object selector:(SEL)selector;
- (NSString*)stringByConcatenatingObjectsAsCommandLineArguments;
- (NSString*)stringByConcatenatingObjectsAsStringList;
- (NSArray*)arrayByExtractingCommandLineArgumentsHavingPrefix:(NSString*)prefix;
- (NSArray*)arrayByPrefixingObjectsWithString:(NSString*)prefix;
- (NSArray*)arrayByMakingRelativePathsAbsoluteUsingBasePath:(NSString*)path;
- (NSString*)PBX_longestCommonPrefixForStrings;
- (NSArray*)arrayByRecursivelyElidingEmptyStringValuesForDictionaryKeysInSet:(id)set;
- (NSArray*)arrayByMakingObjectsPerformSelector:(SEL)selector withObject:(id)object;
- (NSArray*)arrayByMakingObjectsPerformSelector:(SEL)selector;
- (BOOL)areAllObjectsKindOfClass:(Class)class;
- (NSArray*)subarrayToIndex:(unsigned)index;
- (NSArray*)subarrayFromIndex:(unsigned)index;
- (id)firstObject;
- (id)secondObject;
- (id)thirdObject;
- (id)fourthObject;
- (id)preantepenultimateObject;
- (id)antepenultimateObject;
- (id)penultimateObject;
@end

@interface NSString (TSFoundationExtra)
+ (NSString*)stringWithHexRepresentationOfBytes:(const void*)bytes length:(unsigned)length;
+ (NSString*)stringWithBase64RepresentationOfBytes:(const void*)bytes length:(unsigned)length;
+ (NSString*)stringWithUnicodeInvisibleSeparatorCharacter;
+ (NSString*)stringWithUnicodeInvisibleTimesCharacter;
+ (NSString*)stringWithHexadecimalRepresentationOfUniqueIdentifier;
+ (NSString*)stringWithBase64RepresentationOfUniqueIdentifier;
- (BOOL)boolValue;
- (NSString*)stringByRemovingLeadingAndTrailingCharactersFromSet:(NSCharacterSet*)set;
- (NSString*)stringByRemovingLeadingAndTrailingWhitespace;
- (NSString*)stringByRemovingLeadingAndTrailingWhitespaceAndNewlines;
- (NSString*)stringByRemovingPrefix:(NSString*)prefix;
- (NSString*)stringByRemovingSuffix:(NSString*)suffix;
- (NSString*)stringByQuotingOnlyIfNeeded:(BOOL)ifNeeded quoteTabsAndEOLs:(BOOL)quoteTabsAndEOLs quoteHighBitUnichars:(BOOL)quoteHighBits;
- (NSString*)stringByQuotingIfNeeded;
- (NSString*)stringByQuotingWhitespaceIfNeeded;
- (NSString*)PBX_stringByReplacingBackslashWithSlash;
- (NSString*)stringByReplacingCharacter:(unsigned short)oldChar withCharacter:(unsigned short)newChar;
- (NSString*)stringByReplacingSubstring:(NSString*)oldString withString:(NSString*)newString;
- (NSString*)stringByAppendingPathSeparatorIfNeeded;
- (NSDictionary*)dictionaryByParsingAsSimpleAssignmentsAndGetLocalizedErrorString:(NSString**)error;
- (NSString*)substringAfterString:(NSString*)string crossingLineBoundaries:(BOOL)cross;
- (NSString*)substringBeforeString:(NSString*)string crossingLineBoundaries:(BOOL)cross;
- (NSString*)substringBetweenString:(NSString*)startString andString:(NSString*)endString crossingLineBoundaries:(BOOL)cross;
- (NSString*)firstMatchingPrefixFromArray:(NSArray*)prefixes;
@end

@interface NSMutableData (TSFoundationExtra)
- (void)appendCStringCharacters:(const char*)cstring;
- (void)appendUnsignedLEB128:(unsigned long)uleb128;
- (void)appendSignedLEB128:(long)leb128;
@end

@interface NSData (TSFoundationExtra)
- (id)initWithHexRepresentationOfBytes:(const void*)bytes length:(unsigned)length;
- (id)initWithBase64RepresentationOfBytes:(const void*)bytes length:(unsigned)length;
@end

@interface NSObject (TSFoundationExtra)
+ (BOOL)isSubclassOfClass:(Class)class;
+ (id)allSubclasses;
- (void)swizzleToClass:(Class)class;
- (void)performSelector:(SEL)selector withEachObjectInArray:(NSArray*)array withSecondObject:(id)obj2 inReverseOrder:(BOOL)reverse;
- (void)performSelector:(SEL)selector withEachObjectInArray:(NSArray*)array inReverseOrder:(BOOL)reverse;
- (void)performSelector:(SEL)selector withEachObjectInArray:(NSArray*)array withSecondObject:(id)obj2;
- (void)performSelector:(SEL)selector withEachObjectInArray:(NSArray*)array;
- (void)performSelector:(SEL)selector withEachKeyAndObjectInDictionary:(NSDictionary*)dict withThirdObject:(id)obj3;
- (void)performSelector:(SEL)selector withEachKeyAndObjectInDictionary:(NSDictionary*)dict;
- (id)forEachObjectInArray:(id)fp8;
- (id)forEachObjectInDictionary:(id)fp8;
- (id)forEachObjectInSet:(id)fp8;
@end

@interface TSPropertyListDictionary : NSDictionary
{
    NSDictionary*	_dict;
    NSString*		_localizedDesc;
    NSBundle*		_bundle;
    NSDictionary*	_localizationDict;
}
+ (id)propertyListDictionaryWithDictionary:(NSDictionary*)dict;
+ (id)propertyListDictionaryWithContentsOfString:(NSString*)string;
+ (id)propertyListDictionaryWithContentsOfFile:(NSString*)path encoding:(unsigned)encoding;
- (id)initWithDictionary:(NSDictionary*)dict;
- (id)initWithContentsOfString:(NSString*)string;
- (id)initWithContentsOfFile:(NSString*)path encoding:(unsigned)encoding;
- (NSString*)localizedMessageDescription;
- (void)setLocalizedMessageDescription:(NSString*)description;
- (NSBundle*)bundle;
- (void)setBundle:(NSBundle*)bundle;
- (NSDictionary*)localizationDictionary;
- (void)setLocalizationDictionary:(NSDictionary*)dict;
- (unsigned)count;
- (NSEnumerator*)keyEnumerator;
- (NSObject*)objectForKey:(NSString*)key;
- (NSObject*)objectOrNilForKey:(NSString*)key;
- (NSString*)stringForKey:(NSString*)key;
- (NSString*)stringOrNilForKey:(NSString*)key;
- (NSData*)dataForKey:(NSString*)key;
- (NSData*)dataOrNilForKey:(NSString*)key;
- (NSDictionary*)dictionaryForKey:(NSString*)key;
- (NSDictionary*)dictionaryOrNilForKey:(NSString*)key;
- (NSArray*)arrayForKey:(NSString*)key;
- (NSArray*)arrayOrNilForKey:(NSString*)key;
@end

@interface NSString (TSPathUtilities)
- (NSString*)PBX_stringByResolvingSymlinksInPath;
- (NSString*)stringByMakingPathRelativeToPath:(NSString*)path;
- (NSString*)regionVariantName;
- (NSString*)platformName;
- (NSString*)stringByMakingPathPlatformGeneric;
- (NSString*)stringByMakingPathPlatformSpecific:(id)plateform;
- (int)comparePaths:(NSString*)path;
- (NSString*)stringByCanonicalizingPathUsingBasePath:(NSString*)base;
- (NSString*)stringByCanonicalizingPath;
@end
