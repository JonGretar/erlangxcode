//
//  ErlCLinkerSpecification.m
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 27.9.2008.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "EXLinkerSpecificationErlc.h"
#import "XCPBuildSystem.h"
#import "XCPDependencyGraph.h"
#import "XCPSupport.h"

@implementation EXLinkerSpecificationErlc



- (NSArray*) computeDependenciesForFilePaths:(NSArray*)inputs
								  outputPath:(NSString*)output
						inTargetBuildContext:(PBXTargetBuildContext*)context
{
	//	FILE* CSDumpFile = fopen( "/Users/susan/CSDumpFile.txt", "a");
	//	fprintf( CSDumpFile, "In Linker\n");
	
	// compute output paths and nodes
	output = [context expandedValueForString:output];
	
	//	fprintf( CSDumpFile, "  - output = %s\n", [output cString]);
	
	XCDependencyNode* outputNode = [context dependencyNodeForName:output];
	XCDependencyCommand* depLink = [outputNode producerCommand];
	
	NSString* OutputArgument = [NSString stringWithString:@"-out:"];
	OutputArgument = [OutputArgument stringByAppendingString:output];
	[depLink addArgument:OutputArgument];
	[depLink addArgument:[context expandedValueForString:@"$(TARGET_TYPE)"]];
	
	//	fprintf( CSDumpFile, "  Command is now: %s\n", [[depLink displayString] cString]);
	
	// Anticipated file type(s)
	PBXFileType* assemblyFileType = (PBXFileType*)[PBXFileType specificationForIdentifier:@"compiled.mono.library"];
	
	NSEnumerator* AssembliesEnum = [[context linkedLibraryPaths] objectEnumerator];
	NSString* Assembly;
	while( (Assembly = [AssembliesEnum nextObject]) != nil)
	{
		Assembly = [context expandedValueForString:Assembly];
		PBXFileType* type = [PBXFileType fileTypeForFileName:[Assembly lastPathComponent]];
		
		if( [type isKindOfSpecification:assemblyFileType])
		{
			// Assembly file
			//			fprintf( CSDumpFile, "  - Adding library file: %s\n", [Assembly cString]);
			
			XCDependencyNode* libraryNode = [context dependencyNodeForName:Assembly createIfNeeded:YES];
			[outputNode addDependedNode:libraryNode];
			NSString* ReferenceEntry = [NSString stringWithFormat:@"%@%@", @"-reference:", Assembly];
			[depLink addArgument:ReferenceEntry];
		}
		else
		{
			//			fprintf( CSDumpFile, "  - Skipping file %s of type %s\n", [Assembly cString], [[type identifier] cString]);
			
			[context addDependencyAnalysisWarningMessageFormat:
			 @"warning: skipping file '%@' (unexpected file type '%@' in link phase)",
			 Assembly, [type identifier]];
		}
	}
	
	//	[context writeToGraphVizFileAtPath:@"/Users/susan/DumpDependency.dot"];
	
	//	fprintf( CSDumpFile, "---Completed Link\n");
	//	fclose( CSDumpFile);
	
	return [NSArray arrayWithObject:outputNode];
}


- (BOOL)acceptsInputFileType:(id)type
{
	// some types
	PBXFileType* assemblyFileType = (PBXFileType*)[PBXFileType specificationForIdentifier:@"compiled.mono.library"];
	
	PBXFileType* FileType = (PBXFileType*)type;
	BOOL Result = [FileType isKindOfSpecification:assemblyFileType];
	
	return Result;
}


@end
