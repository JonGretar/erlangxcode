#!/usr/bin/env ruby

# copyresources.rb
# ErlangPlugin
#
# Created by Jón Grétar Borgþórsson on 21.10.2008.

# TODO: Make this to some validation and more.

require 'ftools'

File.copy(ARGV[0], ARGV[1])