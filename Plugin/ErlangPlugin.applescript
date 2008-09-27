on plugin loaded theBundle

	-- Make a new script
    script goToWebsiteErlangX
        on choose menu item theObject
            tell application "Safari"
				make new document at end of documents
				set url of document 1 to "http://medevyoujane.com/erlangx"
			end tell
        end choose menu item
    end script
	
	    script goToWebsiteErlangDoc
        on choose menu item theObject
            tell application "Safari"
				make new document at end of documents
				set url of document 1 to "http://erlang.org/doc.html"
			end tell
        end choose menu item
    end script
 
    -- Make a new plugin menu
    set erlangMenu to make new menu at end of menus of main menu  with properties  {title:"ErlangX", name:"erlangx main menu"}
	
	set erlangMenuItem to make new menu item at beginning of menu items  of erlangMenu  with properties {title:"Erlang Docs", name:"visiterlangdocs"}
	set script of erlangMenuItem to goToWebsiteErlangDoc
 
    set erlangMenuItem to make new menu item at beginning of menu items  of erlangMenu  with properties {title:"ErlangX Website", name:"visiterlangxwebsite"}
	set script of erlangMenuItem to goToWebsiteErlangX

end plugin loaded
