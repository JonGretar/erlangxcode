//
//  ErlCCompilerSpecification.m
//  ErlangPlugin
//
//  Created by Jón Grétar Borgþórsson on 27.9.2008.
//

#import "EXCompilerSpecificationErlc.h"
#import "XCPBuildSystem.h"
#import "XCPDependencyGraph.h"
#import "XCPSupport.h"

@implementation EXCompilerSpecificationErlc


- (NSArray*) computeDependenciesForInputFile:(NSString*)input ofType:(PBXFileType*)type
									 variant:(NSString*)variant architecture:(NSString*)arch
							 outputDirectory:(NSString*)outputDir
						inTargetBuildContext:(PBXTargetBuildContext*)context
{
	//FILE* CSDumpFile = fopen( "/Users/jongretar/Temp/EPDumpFile.txt", "a");
	//fprintf( CSDumpFile, "In Compiler\n");
	
    // compute input path (for variable substitution)
    input = [context expandedValueForString:input];
    
    // compute output path
    NSString* output = [outputDir stringByAppendingPathComponent:[[input lastPathComponent] stringByDeletingPathExtension]];
    output = [context expandedValueForString:output];
    
    // create dependency nodes
    XCDependencyNode* outputNode = [context dependencyNodeForName:output createIfNeeded:YES];
    XCDependencyNode* inputNode = [context dependencyNodeForName:input createIfNeeded:YES];
    
    // create compiler command
    XCDependencyCommand* dep = [context
								createCommandWithRuleInfo:[NSArray arrayWithObjects:@"ERLC:",[context naturalPathForPath:input],nil]
								commandPath:[context expandedValueForString:[self path]]
								arguments:nil
								forNode:outputNode];
    [dep setToolSpecification:self];
    [dep addArgumentsFromArray:[self commandLineForAutogeneratedOptionsInTargetBuildContext:context]];
    [dep addArgumentsFromArray:[[context expandedValueForString:@"$(build_file_compiler_flags)"] arrayByParsingAsStringList]];
    //[dep addArgument:@"-o"];
    //[dep addArgument:output];
    [dep addArgument:input];
    
    // create dependency rules
    [outputNode addDependedNode:inputNode];
	
    // update source-compiled links
    [context setCompiledFilePath:output forSourceFilePath:input];
    
	
    // return output object node (Xcode will automaticaly add .o files to $(object_files))
    return [NSArray arrayWithObject:outputNode];
}


@end
