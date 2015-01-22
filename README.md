#### CSS Sort (aka Knife)

A command-line utility that takes a CSS file via stdin and sends a filtered/sorted version to stdout. No in-place sorting of css files is supported!
 
**Usage**: cssort [-cZ] [ -d N ] [ -f target_file_name] [ -o output_file ] 

-c, include comments

-d N, debug level

  1 - validate CSS (default)
  
  2 - scan for duplicate entries
  
-f, target filename

-m, minimize css

-M, merge duplicate entries within same block level

-Z, include leading non-alphabetic characters like '.' and '#' in sort procedure

features under consideration:

+ Implementing it as a web service

+ Structural requirements for the inclusion of comments

+ Minifier Switch

+ Nested block logic

  I.E., Keep a count of brace nesting level so you can treat nested tags (.e.g. media query style rules) as a separate sort group if needed.

