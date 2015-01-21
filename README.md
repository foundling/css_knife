#### CSS Sort

A utility that sorts your CSS file and sends it to stdout. No in-place sorting supported.
 
**Usage**: cssort [ -f target_file_name] [ -o output_file ] [-Z ] 

-f, target filename
-Z, include leading non-alphabetic like '.' and '#' in sort procedure

features in consideration:

Implementing it as a web service
Sort Properties Switch
Minifier Switch
Nested Block logic
  I.E., Keep a count of brace nesting level so you can treat nested tags (.e.g. media query style rules) as a separate group if needed.

