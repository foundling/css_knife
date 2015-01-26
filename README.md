#### knife v 0.0

A command-line utility that takes a CSS file via stdin and sends a filtered/sorted version to stdout or to an output file that is not the same as the source file. No in-place sorting of css files is supported!
 
**Usage**: knife [-DZ ] [ -f target_file_name] [ -o output_file ] 

-D, find duplicate selectors

-o, send stdout to a file. cannot be the name of the source file

-p, sort properties only, do not sort css rules

-f, target filename

-Z, include leading non-alphabetic characters like '.' and '#' in sort procedure



features under consideration:

+ Implementing it as a web service

+ Structural requirements for the inclusion of comments

+ Nested block logic

  I.E., Keep a count of brace nesting level so you can treat nested tags (.e.g. media query style rules) as a separate sort group if needed.
