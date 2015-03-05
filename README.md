    knife v -0.3

    CSS Knife: industrial-strength CSS sorting.

    USAGE: knife [ -sdSDonZ ] <FILENAME> [ -o output_file ] 

    default: stats, equiv to -S

    -s, sort css selectors
    -d, sort by declarations
    -S, outputs stats (errors, duplicates)
    -D, find duplicate selectors
    -o, write stdout to a file. cannot be the name of the source file
    -n, do not sort css declarations
    -Z, include leading non-alphabetic characters like '.' and '#' in sort procedure.  
    
    This option is positional and         applies to the next specified -r or -d flag.  If none is present, 
