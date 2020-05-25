# SHEX

Arduino library to generate hex dump over Serial

# Description

SHEX is a simple library that wraps the Serial output side (by default) and
generates an hexdump of all data that is printed. 16 bytes per row.

The default output format is 
```
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx
0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx

0xABCDABCD  xx xx xx xx  xx xx xx xx  xx xx xx xx  xx xx xx xx 
```
with a separator line after each 8th line.

The constructor has a length parameter which can be used to have another
number of bytes per row. After construction this cannot be changed, at
least not in this initial release. 

The only thing one can toggle is HEX output or pass through by means 
of **setHEX(bool)**.
This makes it possible to switch between the modes e.g. between 
'debugging' and 'release' mode.

### ideas for the future

Although no follow up release is really planned, some ideas are kept here
so they won't get lost.

- Optional ASCII colomn in the output format ( . if not printable) e.g.
```
0xABCDABCD  xx xx xx xx xx xx xx xx xx    c.cc c..c
```

- bytes per line: runtime configurable

- seperarator: runtime configurable; 

- headerline: runtime configurable; optional combined with separator

- HEX reader: converts dump format to a normal stream again.

- better name for the class?

# Operational

See examples
