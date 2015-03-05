    CSS Knife: industrial-strength CSS sorting.

    USAGE: knife [ -sdSDonZ ] [ <FILENAME> ]  [ -o <OUTPUT_FILE> ] 
    HARD DEPENDENCIES: tinycss parsing library
    When no arguments are passed, the default flag is -S, output stats

    -s, sort css selectors
    -d, sort by declarations
    -S, outputs stats (errors, duplicates)
    -D, find duplicate selectors
    -o, write stdout to a file. cannot be the name of the source file
    -Z, include leading non-alphabetic characters like '.' and '#' in sort procedure.  
    This option is positional and must come before a -r or -d flag.  If no -r or -d flag
    follows the -Z flag, it is ignored.
