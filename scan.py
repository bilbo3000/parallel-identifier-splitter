#!/usr/bin/python 

import os 

outDir = os.path.join(os.curdir, "out_1"); 
filenames =  os.listdir(outDir);
t1 = []; 
t2 = []; 

for filename in filenames:
    filepath = os.path.join(outDir, filename); 
    fin = open(filepath, 'r');
    line = fin.readline(); 
    while line != "": 
        line = line.rstrip('\n'); 

        if line[:2] == "t1": 
            t1.append(int(line[3:])); 
        if line[:2] == "t2": 
            t2.append(int(line[3:])); 
        line = fin.readline(); 
    fin.close(); 

print "t1 min:", min(t1);
print "t2 max:", max(t2); 
