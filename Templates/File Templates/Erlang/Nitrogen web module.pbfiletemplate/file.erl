%%%-------------------------------------------------------------------
%%% File          : «FILENAME»
%%% Author        : «FULLUSERNAME»
%%% Organization  : «ORGANIZATIONNAME»
%%% Project       : «PROJECTNAME»
%%% Description   : 
%%%
%%% Created       :  «DATE»
%%%-------------------------------------------------------------------
-module(«FILEBASENAME»).
-include_lib ("nitrogen/include/wf.inc").
-author(«USERNAME»).
-compile(export_all).

main() -> 
	#template { file="./wwwroot/template.html" }.

event(_) -> ok.