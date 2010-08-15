/*
	XCPBuildSystem.h - XCode Plugin API
	Copyright 2005-2008 Damien Bobillot.
	Distributed under the GPL v3 licence.
	
	Define a function to retreive all files in the framework build phase.
*/

#import "XCPBuildSystem.h"
#import "XCPSpecifications.h"
#import <objc/objc-class.h>
#import <Foundation/Foundation.h>

/*
	Some hidden declarations
*/

@interface PBXFileReference
- (NSArray*)referencesForBuilding;
- (NSString*)path;
- (NSString*)unexpandedAbsolutePath;
- (PBXFileType*)fileType;
@end

@interface PBXBuildFile
- (PBXFileReference*)fileReference;
@end

@interface PBXBuildPhase
#if XCODE_VERSION < 22
- (NSArray*)filteredBuildFilesForTargetBuildContext:(PBXTargetBuildContext*)context;
#else
- (NSArray*)buildFiles;
#endif
@end

@interface PBXTarget
- (PBXBuildPhase*)defaultFrameworksBuildPhase;
@end

@interface PBXTargetBuildContext (BDPrivate)
- (PBXTarget*)target;
@end

/*
	linkedLibraryPaths : get files in the "link with library & framework" phase
*/
@implementation PBXTargetBuildContext (BDExtensions)
- (NSArray*)linkedLibraryPaths {
	// From reverse engineering of the Ld linker
	NSMutableArray* paths = [NSMutableArray arrayWithCapacity:20];
	
	PBXBuildPhase* buildPhase = [[self target] defaultFrameworksBuildPhase];
#if XCODE_VERSION < 22
	NSEnumerator* buildFileEnum = [[buildPhase filteredBuildFilesForTargetBuildContext:self] objectEnumerator];
#else
	NSEnumerator* buildFileEnum = [[buildPhase buildFiles] objectEnumerator];
#endif
	PBXBuildFile* buildFile;
	while((buildFile = [buildFileEnum nextObject]) != nil) {
	
		NSEnumerator* fileEnum = [[[buildFile fileReference] referencesForBuilding] objectEnumerator];
		PBXFileReference* file;
		while((file = [fileEnum nextObject]) != nil)
			[paths addObject:[file unexpandedAbsolutePath]];
	}
	
	return paths;
}

/*
	Hook -[PBXTargetBuildContext activateImportedFileType:ensureFilesExist:]
*/
static IMP __original_importedFilesForPath_ensureFilesExist = nil;
static NSMutableDictionary* __compilers_with_import = nil;

+ (NSArray*)BDExtensions_importedFilesForPath:(NSString *)path ensureFilesExist:(BOOL)ensure
{
	PBXFileType* type = [PBXFileType fileTypeForFileName:path];
	
	// Check if type is in our list
	NSEnumerator* e = [__compilers_with_import keyEnumerator];
	PBXFileType* t;
	while((t = [e nextObject]) != nil) {
		if(![type isKindOfSpecification:t]) continue;
		XCCompilerSpecification* spec = (XCCompilerSpecification*)[__compilers_with_import objectForKey:t];
		return [spec importedFilesForPath:path ensureFilesExist:ensure inTargetBuildContext:self];
	}
	
	// Type not found, call default code
	return [self BDExtensions_importedFilesForPath:path ensureFilesExist:ensure];
}

+ (void)activateImportedFileType:(PBXFileType*)type withCompiler:(XCCompilerSpecification*)spec
{
	// Setup hook for importedFilesForPath:ensureFilesExist:
	if(__original_importedFilesForPath_ensureFilesExist == nil) {
		__compilers_with_import = [NSMutableDictionary new];
		
		Class c = [self class];
		Method m = class_getInstanceMethod(c, @selector(importedFilesForPath:ensureFilesExist:));
		Method m2 = class_getInstanceMethod(c, @selector(BDExtensions_importedFilesForPath:ensureFilesExist:));
		__original_importedFilesForPath_ensureFilesExist = method_setImplementation(m, method_getImplementation(m2));
	}
	
	// Add include parser for this file type
	[__compilers_with_import setObject:spec forKey:type];
}
@end

@interface PBXFileType (BDExtensions)
- (id) copyWithZone:(NSZone*)zone;
@end 

@implementation PBXFileType (BDExtensions)
- (id) copyWithZone:(NSZone*)zone { return self; }
@end
