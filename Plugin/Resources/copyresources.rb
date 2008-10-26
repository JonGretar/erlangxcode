#!/usr/bin/env ruby

# copyresources.rb
# ErlangPlugin
#
# Created by Jón Grétar Borgþórsson on 21.10.2008.

# TODO: Make this to some validation and more.

require 'ftools'
require 'optparse'

# Gather command line options.
OPTIONS = {
    :OutputDir => nil,          # Path of the output directory [required]
	:Version => "1",         # Version [default 1]
}

begin
    # Any errors will cause an exception.
    opts = OptionParser.new() do |opts|
        opts.banner = "usage: #{File.basename($0)} [options] SRCFILE ... DSTDIR"
		
		opts.on("-v", "--version VSN", "Version") do |version|
            OPTIONS[:Version] = version
        end
        
		opts.on("-o", "--outdir DIR", "Specify the output directory") do |path|
            if OPTIONS[:OutputDir] then
                puts "#{File.basename($0)}: output directory specified more than once"
                puts opts
                exit 1
            end
            OPTIONS[:OutputDir] = path
        end
		
        opts.on_tail("-h", "--help", "Show this message") do
            puts opts
            exit 1
        end
    end
    opts.parse!
rescue
    # Exception was raised; this is an unrecoverable error.
    puts "#{File.basename($0)}: #{$!}"
    puts opts
    exit 1
end


# Make sure we have the inputs we need (though some may come from defaults).
if OPTIONS[:OutputDir] == nil || OPTIONS[:OutputDir] == '' then
    puts "#{File.basename($0)}: no output directory specified"
    puts opts
    exit 1
end


# ARGV now just contains the input files.  We process each one in turn.
for path in ARGV do
    # Read the file contents.
    begin
        f = open(path)
        fileContents = f.read()
        f.close()
    rescue
        puts "#{path}: #{$!.message[/[^-]*/]}"
        exit 1
    end
	
	fileContents.gsub!(/\#\{VERSION\}/, OPTIONS[:Version])
	
	#Write The File Contents
	begin
		newpath = File.join( OPTIONS[:OutputDir] + "/" + File.basename(path) )
		File.open(newpath, 'w') { |f| f.write(fileContents) }
    rescue
        puts "#{newpath}: #{$!.message[/[^-]*/]}"
        exit 1
    end
	
end
