/*
	XCPDependencyGraph.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
*/

#import <Foundation/Foundation.h>

@class PBXTargetBuildContext;
@class XCCommandLineToolSpecification;
@class XCDependencyCommand;

/*
	A dependency node
*/
@interface XCDependencyNode : NSObject {
#if XCODE_VERSION == 23
	char _members_XCDependencyNode[0x68 - 0x4];
#endif
}

// Accessors
- (PBXTargetBuildContext*)buildContext;
- (NSString*)name;
- (BOOL)isVirtual;
- (XCDependencyCommand*)command;
- (NSString*)shortNameForDebugging;

// Graph data
- (void)addDependedNode:(XCDependencyNode*)node;
- (void)addIncludedNode:(XCDependencyNode*)node;
- (void)removeAllIncludedNodes;

- (XCDependencyNode*)includedNodes;
- (XCDependencyNode*)includingNodes;
#if XCODE_VERSION < 22
- (XCDependencyNode*)dependedNodes;
- (XCDependencyNode*)dependingNodes;
#else
- (id)producerCommands;
- (id)consumerCommands;
- (id)producerCommand;
#endif

// Paths
- (NSString*)path;
- (NSArray*)paths;
#if XCODE_VERSION < 22
- (void)addPath:(NSString*)path;
#endif

// Included file managment
- (void)setScansFileContentsForIncludes:(BOOL)scan;

//
- (BOOL)isAlwaysOutOfDate;
- (void)setAlwaysOutOfDate:(BOOL)always;
- (BOOL)dontCareIfExists;
- (void)setDontCareIfExists:(BOOL)dontCare;
#if XCODE_VERSION >= 23
- (BOOL)dontCareAboutTimestamp;
- (void)setDontCareAboutTimestamp:(BOOL)fp8;
#endif
@end

/*
	A dependency command
*/
@interface XCDependencyCommand : /*XCWorkQueueCommand*/ NSObject
{
#if XCODE_VERSION == 23
	char _members_XCDependencyCommand[0x7c - 0x4];
#endif
}

// Accessors
- (PBXTargetBuildContext*)buildContext;
- (NSString*)name;
- (unsigned)commandNumber;
- (NSString*)displayString;
- (NSString*)shortNameForDebugging;
- (NSString*)description;

- (unsigned)phaseNumber;
- (void)setPhaseNumber:(unsigned)number;

- (NSArray*)inputNodes;
- (void)addInputNode:(XCDependencyNode*)node;

- (NSArray*)outputNodes;
- (void)addOutputNode:(XCDependencyNode*)node;

- (XCCommandLineToolSpecification*)toolSpecification;
- (void)setToolSpecification:(XCCommandLineToolSpecification*)spec;

- (id)commandPath;
- (void)setCommandPath:(id)path;

- (NSString*)workingDirectoryPath;
- (void)setWorkingDirectoryPath:(NSString*)path;

// Command arguments
- (void)addArgument:(NSString*)arg;
- (void)addArguments:(NSString*)args;
- (void)addArgumentsFromArray:(NSArray*)args;

// Command environment
- (void)setEnvironment:(NSDictionary*)env;
- (void)addEnvironmentValue:(NSString*)value forKey:(NSString*)key;
- (void)addEnvironmentEntriesFromDictionary:(NSDictionary*)env;

// Included file managment
- (BOOL)caresAboutIncludes;
- (void)setCaresAboutIncludes:(BOOL)care;

/*
- (id)ruleInfo;
- (void)setRuleInfo:(id)rule;
- (void)fileMayHaveChanged;
- (id)dependencyNode;

#if XCODE_VERSION >= 23
- (id)filePathsToRemove;
- (void)addFilePathToRemove:(id)fp8;
#endif
*/
@end
