REM File: genDepGraph.bat
REM Author: Bob Rubbens - Knights of the Compiler
REM Creation date: su 23-08-2014
REM Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens) 

tup graph . | dot -Tpng > graph.png
