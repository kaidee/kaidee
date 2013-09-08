#========================================================================
#   FileName: sudoku.rb
#     Author: vividlee2010
#      Email: vividlee2010@gmail.com
#   HomePage: http://www.vividlee2010.com
# LastChange: 2012-04-23 20:51:35
#========================================================================
#
#	This module defines a Sudoku::Puzzle class to represent a 9x9
#	Sudoku puzzle and also defines exception classes railsed for
#	invalid input and over-constrained puzzle. This module also defines
#	the method Sudoku. solve to a puzzle. The solve method uses
#	the Sudoku.scan method, which is also defined here.
#
#	Use this module to solve Sudoku puzzles with code like this:
#	require 'sudoku'
#	puts Sudoku.solve(Sudoku::Puzzle.new(ARGF.readlines))
#
module Sudoku
	#
	#	The Sudoku::Puzzle class represents the state of a 9x9 Sudoku puzzle.
	#
	#	Some definitions and terminology used in this implementation:
	#
	#	-Each element of a puzzle is called a "cell".
	#	-Rows ane columns are numbered from 0 to 8, and the coordinates [0,0]
	#	 refer to the cell in the upper-left corner of the puzzle.
	#	-The nine 3x3 subgrids are known as "boxes" andare also numbered from
	#	 0 to 8, ordered from left to right and top to bottom. The box in
	#	 the upper-left is box 4. The box in the lower-right is box 8.
	#
	#	Create a new puzzle with Sudoku::Puzzle.new,specifying the initial
	#	state as a string or as an array of strings. The string(s) should use
	#	the characters 1 through 9 for the given values, and '.' for cells
	#	whose value is unspecified. Whitespace in zhe iput is ignored.
	#
	#	Read and write access to individual cells of the puzzle is through the
	#	[] and []=operators,which expect two-dimensional [row,column] indexing.
	#	These methods use numbers (notcharacters) 0 to 9 for cell contents.
	#	0 represents an unknown value.
	#	
	#	The has_duplicates? predicate returns true if the puzzle is invalid
	#	beacause any rowm column, or box includes the same digit twice.
	#
	#	The has_unknown method is an iterator that loops through the cells of
	#	the puzzle and invokes the associate block once for each cell whose
	#	value is unknown.
	#
	#	The possible method returns an array of integers in the range 1..9.
	#	The elements of the array are the only values allowed in the specified
	#	cell. If this array is empty, then the puzzle is over-specified and 
	#	cannot be solved. If the array has only one element, then that element 
	#	must be the value for that cell of the puzzle.
	#
	class Puzzle
		
		#	These constants are used for translating between the external
		#	string representation of a puzzle and the internal representation.

		ASCII = ".123456789"
		BIN = "\000\001\002\003\004\005\006\007\010\011"
		
		#	This is the initialization method for the class. It is automatically
		#	invoked on new Puzzle instances created with Puzzle.new. Pass the input
		#	puzzle as an array of lines or as a single string. Use ASCII difits 1
		#	to 9 and use the'.' character for unknown cells. Whitespace,
		#	including newlines, will be stripped.
		def initialize(lines)
			if (lines.respond_to? :join)	#	If argument looks like an array of lines
				s = lines.join				#	Then join them into a single string
			else							#	Otherwise, assume wi have a string
				s = lines.dup				#	And make a private copy of it
			end

			#	Remove whitespace (including newlines) from the data
			#	The '!' in gsub! indicates that this is a mutator method that
			#	alters the string directly rather than making a copy.
			s.gsub!(/\s/, "")	#	/\s/ is a Regexp thar matches any whitespace

			#	Raise an exception if the input is the wrong size.
			#	Note that we use unless instead of if, and use it in modifier form
			if i = s.index(/[^123456789\.]/)
				#	Include the invalid characetr in the error message.
				#	Note the Ruby expression inside #{} in string literal.
				raise Invalid, "Illegal character #{s[i,1]} in puzzle"
			end

			#	The following two lines convert our string of ASCII characters
			#	to an array of integers, using two powerful String methods.
			#	The resulting array is stored in the instance variable @grid
			#	The number 0 is used to represent an unknown value.
			s.tr!(ASCII,BIN) 		#	Translate ASCII characters into bytes
			@grid = s.unpack('c*') #	Now unpack the bytes into an array of numbers

			#	Make sure that the rows, columns, and boxes have no duplicates.
			rails Invalid,"initial puzzle has duplicates" if has_duplicates?
			end
			# Return the state of the puzzle as a string of 9 lines with 9
			# characters (plus newline) each.
			def to_s
				# This method is implemented with a single line of Ruby magic that
				# reverses the steps in the initialize() method.Writing dense code
				# like this is probably not good coding style, but it demonstrates
				# the power and expressiveness of the language.
				# 
				# Broken down, the line below works like this:
				(0..8).collect{|r| @grid[r*9,9].pack('c9')}.join("\n").tr(BIN,ASCII)
			end
			# Return a duplicate of this Puzzle object.
			# This method overrides Object.dup to copy the @grid array.
			def dup
				copy = super			# Make a shallow copy by calling Object.dup
				@grid = @grid.dup       # Make s new copy of the internal data
				copy					# Return the copied object
			end

			# We overrides the array access operator to allow acccess to the
			# indivedual cells of a puzzle. Puzzles are two-dimensional,
			# and must be indexed with row and column coordinates into a one-dimensional
			def [](row,col)
				# Convert two-dimensional (row,col) coordinates into a one-dimensional
				# array index and get and return the cell value at that index
				@grid[row*9 + col]
			end

			# This method allows the array access operator to be used on the
			# lefthand side of an assignment operation. It sets the value of
			# the cell at (row,col) to newvalue.
			def [] = (row, col, newvalue)
				# Raise an exception unless the new value is in the rang 0 to 9.
				unless (0..9).include? newvalue
					raise Invalid, "Illegal cell value"
				end
				# Set the appropriate element of the internal array to the value.
				@grid[row*9 + col] = newvalue
			end

			# This array maps from one-dimensional grid index to box number.
			# It is used in the method below. The name BoxOfIndex begins with a 
			# capital letter, so this is a constant. Also, the array has been 
			# frozen, so it cannot be modified.
			BoxOfIndex = [
				0,0,0,1,1,1,2,2,2,0,0,0,1,1,1,2,2,2,0,0,0,1,1,1,2,2,2,
				3,3,3,4,4,4,5,5,5,3,3,3,4,4,4,5,5,5,3,3,3,4,4,4,5,5,5,
				6,6,6,7,7,7,8,8,8,6,6,6,7,7,7,8,8,8,6,6,6,7,7,7,8,8,8,
				].freeze

			# This method difines a custom looping construct (an "iterator") for 
			# Sudoku puzzles. For each cell whose value is unknown, this method 
			# passes ("yields") the row number, column number, and box number to the 
			# block associated with this iterator.
			def each_unknown
				0.upto 8 do |row|           # For each row
					0.upto 8 do |col|       # For each column
						index = row*9 + col 
						next if @grid[index] != 0
						box = BoxOfIndex[index]
						yield row, col, box 
					end
				end
			end

			# Returns true if any row, column, or box has duplicates.
			# Otherwise returns false. Duplicates in rows, columns, or boxes are not 
			# allowsd in Sudoku, so a return value of true means an invalid puzzle.
			def has_duplicates?
				# uniq! returns nil if all the elements in an array are unique.
				# So if uniq! returns something then the board has duplicates.
				0.upto(8) {|row| return true if rowdigits(row).uniq! }
				0.upto(8) {|col| return true if coldigits(col).uniq! }
				0.upto(8) {|box| return true if boxdigits(box).uniq! }

				false  # If all the tests have passed, then the board has no duplicates
			end

			# This array holds a set of all Sudoku digits.Used below. 
			AllDigits = [1,2,3,4,5,6,7,8,9].freeze

			# Return an array of all values that could be placed in the cell
			# at (row, col) without creating a duplicate in the row, column, or box.
			# Note that the + operator