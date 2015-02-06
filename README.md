#### knife v 0.0

A command-line utility that takes a CSS file via stdin, alphabetizes it, and sends the newly sorted file to stdout or to an output file that is not the same as the source file. Sorry, but no in-place sorting of css files is supported at this time.

Also, comments are not supported, so this thing is pretty much useless, so don't use it.  /warning

The end goal, however, is to be of industrial-strength use.
 
 
 
**Usage**: knife [-DZ ] [ -f target_file_name] [ -o output_file ] 

-D, find duplicate selectors

-f, target filename

-o, send stdout to a file. cannot be the name of the source file

-p, sort properties only, do not sort css rules

-Z, include leading non-alphabetic characters like '.' and '#' in sort procedure



features under consideration:

+ Implementing it as a web service

+ Structural requirements for the inclusion of comments

+ Nested block logic

  I.E., Keep a count of brace nesting level so you can treat nested tags (.e.g. media query style rules) as a separate sort group if needed.
