#!/usr/bin/python 

'''
Parser that separate identifiers and oracle. 
Dongpu
11/30/2013
'''

import os; 

infilename = "WDM_identifiers3.csv"; 
outfilename = "identifier.txt"; 
oraclename = "oracle.txt"; 

infile = open(infilename, "r");
outfile = open(outfilename, "w");
oraclefile = open(oraclename, "w");  

line = infile.readline(); 

while (line): 
	line = line.rstrip('\n'); 
	result = line.split(','); 
	outfile.write(result[0] + '\n');  # identifier 
	oraclefile.write(result[1] + '\n');  # oracle 
	line = infile.readline(); 
	
infile.close();  
outfile.close(); 
oraclefile.close(); 
