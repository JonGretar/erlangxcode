/*
	XCPBuildSystem.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
*/

#import <Foundation/Foundation.h>

@class XCDependencyNode;
@class XCDependencyCommand;
@class PBXFileType;
@class XCCompilerSpecification;

/*
	Generic build context
*/
@interface PBXBuildContext : NSObject {
#if XCODE_VERSION == 23
	char _members_PBXBuildContext[0x10 - 0x4];
#endif
}

// Accessors
- (id)currentBuildOperation;
- (NSString*)baseDirectoryPath;
#if XCODE_VERSION < 23
- (NSString*)chrootPath;
#endif

// Modify dynamic settings (= globals variables)
- (void)setStringValue:(NSString*)value forDynamicSetting:(NSString*)settingName;
- (void)removeDynamicSetting:(NSString*)settingName;
- (void)prependStringOrStringListValue:(NSString*)value toDynamicSetting:(NSString*)settingName;
- (void)appendStringOrStringListValue:(NSString*)value toDynamicSetting:(NSString*)settingName;
- (void)removeStringOrStringListValue:(NSString*)value fromDynamicSetting:(NSString*)settingName;

// Recursively replace $(VARIABLE) in strings by the value of the build setting VARIABLE
// $(VARIABLE:quote) may be used to automatically quote and escape variable content
#if XCODE_VERSION < 22
- (NSString*)expandedValueForString:(NSString*)string getRecursiveSettingName:(id*)name options:(unsigned)options;
- (NSString*)expandedValueForString:(NSString*)string getRecursiveSettingName:(id*)name;
- (BOOL)expandedValueExistsForString:(NSString*)string;
#else
- (BOOL)expandedValueIsNonEmptyForString:(NSString*)string;
- (BOOL)expandedBooleanValueForString:(NSString*)string;
#endif
- (NSString*)expandedValueForString:(NSString*)string;
- (NSString*)absoluteExpandedPathForString:(NSString*)string;

// Others
- (void)removeAllDynamicSettings;

/*
- (void)pushToolParameterTierBuildSettingsDictionary:(id)tier;
- (void)popToolParameterTierBuildSettingsDictionary;
- (void)setToolParameterTierBuildSettingsDictionaries:(id)tier;
- (void)setHighestTierBuildSettingsDictionaries:(id)tier;
- (void)pushCustomTierBuildSettingsDictionary:(id)tier;
- (void)popCustomTierBuildSettingsDictionary;
- (void)setCustomTierBuildSettingsDictionaries:(id)tier;
- (void)pushDefaultsTierBuildSettingsDictionary:(id)tier;
- (void)popDefaultsTierBuildSettingsDictionary;
- (void)setDefaultsTierBuildSettingsDictionaries:(id)tier;
- (void)setLowestTierBuildSettingsDictionaries:(id)tier;

- (id)propertyExpansionContext;
- (void)setPropertyExpansionContext:(id)fp8;
#if XCODE_VERSION >= 23
- (id)arrayByExpandingEntriesInArray:(id)fp8;
- (id)dictionaryByExpandingEntriesInDictionary:(id)fp8;
#endif
*/
@end

/*
	Context for the target build phase	
*/
//#if XCODE_VERSION < 30
@interface PBXTargetBuildContext : PBXBuildContext
//#else
//@interface PBXTargetBuildContext : PBXBuildContext <XCBuildInfoManagers>
//#endif
{
#if XCODE_VERSION == 23
	char _members_PBXTargetBuildContext[0xd8 - 0x10];
#endif
}

// Accessors
- (id)target;
- (NSString*)productDirectoryPath;
- (NSString*)buildDirectoryPath;
- (NSString*)description;
- (NSString*)baseDirectoryPath;
- (id)presumedBuildAction;
- (id)presumedBuildConfigurationName;
- (id)presumedBuildStyle;

// Natural (= relative to project) to absolute path conversions
- (NSString*)absolutePathForPath:(NSString*)path;
- (NSString*)naturalPathForPath:(NSString*)path;

// Build setting variable containing a list of paths
- (void)addPath:(NSString*)path toFilePathListWithIdentifier:(NSString*)identifier;
- (NSArray*)filePathListWithIdentifier:(NSString*)identifier;

// Dependency nodes
- (XCDependencyNode*)dependencyNodeForName:(NSString*)name createIfNeeded:(BOOL)create;
- (XCDependencyNode*)dependencyNodeForName:(NSString*)name;

// Product nodes
- (void)addProductNode:(XCDependencyNode*)node;

// Dependency commands
- (XCDependencyCommand*)createCommandWithRuleInfo:(NSArray*)info commandPath:(NSString*)path arguments:(NSArray*)args forNode:(XCDependencyNode*)node;

// Generic command creation
- (id)createDirectoryAtPath:(NSString*)path;
- (id)touchFileAtPath:(NSString*)path;
- (id)copyFileAtPath:(NSString*)srcPath toPath:(NSString*)dstPath;
- (id)dittoFileAtPath:(NSString*)srcPath toPath:(NSString*)dstPath;
- (id)moveFileAtPath:(NSString*)srcPath toPath:(NSString*)dstPath;
- (id)makeSymlinkToFileAtPath:(NSString*)originalPath atPath:(NSString*)linkPath;

// Auxiliary file managment
- (void)defineFileContents:(NSData*)content forAuxiliaryFileAtPath:(NSString*)path withPosixPermissions:(unsigned long)perms;
- (NSData*)fileContentsForAuxiliaryFileAtPath:(NSString*)path;
- (void)defineFileContents:(NSData*)content forAuxiliaryFileAtPath:(NSString*)path;
- (id)symlinkContentsForAuxiliarySymlinkAtPath:(NSString*)path;
- (void)defineSymlinkContents:(id)content forAuxiliarySymlinkAtPath:(NSString*)path;
- (BOOL)writeAuxiliaryFiles;

// Compile/source file links
- (void)setCompiledFilePath:(NSString*)compiledPath forSourceFilePath:(NSString*)sourcePath;
- (NSString*)compiledFilePathForSourceFilePath:(NSString*)path;
- (NSString*)sourceFilePathForCompiledFilePath:(NSString*)path;
- (void)clearCompiledFileInfoForFileAtPath:(NSString*)path;
- (void)clearCompiledFileInfoForAllFiles;

// Dependency analysis error messages
- (void)addDependencyAnalysisErrorMessageFormat:(NSString*)format,...;
- (void)addDependencyAnalysisWarningMessageFormat:(NSString*)format,...;

// Included file managment
- (BOOL)shouldScanHeadersOfFileAtPath:(NSString*)path;
- (id)importedFilesForPath:(NSString*)path ensureFilesExist:(BOOL)ensure;
- (id)importedFilesForPath:(NSString*)path;

// Linker parameters setted by compiler
#if XCODE_VERSION >= 23
- (id)compilerRequestedLinkerParameters;
- (void)addCompilerRequestedLinkerParameters:(id)fp8;
- (void)removeAllCompilerRequestedLinkerParameters;
#endif

// Others
- (BOOL)writeToGraphVizFileAtPath:(NSString*)path;
#if XCODE_VERSION >= 22
- (void)createDependencyGraphWithTargetDGSnapshot:(id)dgs;
#endif

/*
- (void)addActiveToolSpecification:(id)fp8;
- (void)setConstantFlags:(id)fp8 forBuildToolWithIdentifier:(id)fp12;

- (void)countBuildFileBaseName:(id)fp8;
- (unsigned)countForBuildFileBaseName:(id)fp8;
- (id)constantFlagsForBuildToolWithIdentifier:(id)fp8;
- (id)preprocessedFilePathForSourceFilePath:(id)fp8;
- (id)disassembledFilePathForSourceFilePath:(id)fp8;
- (id)activeToolSpecifications;
- (id)effectiveSearchPathsForSearchPath:(id)fp8;
- (id)searchPathsForRez;
- (BOOL)isFileUpToDateAtPath:(id)fp8;
- (id)fileInfoValueForKey:(id)fp8 forFileAtPath:(id)fp12;
- (void)setFileInfoValue:(id)fp8 forKey:(id)fp12 forFileAtPath:(id)fp16;

#if XCODE_VERSION < 22
- (id)headermapForGeneratedFiles;
- (id)headermapForOwnTargetHeaders;
- (id)headermapForAllTargetHeaders;
- (id)headermapForProjectHeaders;
- (id)headermap;
#else
- (id)headermapForIdentifier:(id)fp8;
- (void)setHeadermap:(id)fp8 forIdentifier:(id)fp12;
- (id)effectiveHeaderSearchPaths;
- (id)effectiveUserHeaderSearchPaths;
- (id)effectiveFrameworkSearchPaths;
- (id)effectiveLibrarySearchPaths;
- (id)effectiveRezSearchPaths;
#endif
#if XCODE_VERSION >= 23
- (void)removeSearchPathArgumentsFromArrayOfCommandLineArguments:(id)fp8;
#endif
- (id)headerFileSearchContextForSourceFilesUsingCompiler:(id)fp8 languageDialect:(id)fp12;
- (id)preprocessingInfoForIndexingSourceFilesWithCompiler:(id)fp8 languageDialect:(id)fp12;
*/
@end

@interface PBXTargetBuildContext (BDExtensions)
- (NSArray*)linkedLibraryPaths;
+ (void)activateImportedFileType:(PBXFileType*)type withCompiler:(XCCompilerSpecification*)spec;
@end

/*
PBXHeaderFileSearchContext
*/
