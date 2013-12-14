#!/usr/bin/python

import subprocess; 
import sys; 
import os; 
from datetime import datetime; 

if (len(sys.argv) != 2): 
    print "Incorrect number of arguments. "; 
    print "Correct usage: python run.py <algorithm id>";
    print "Algorithms: ";
    print "1) Maximize longest word;";
    print "2) Maximize number of words; ";
    print "3) Minimize number of words. "; 
    sys.exit(1); 

# Algorithm id which algorithm to use  
version = int(sys.argv[1]); 

if (version < 1 or version > 3):
    print "Algorithms: ";
    print "1) Maximize longest word;";
    print "2) Maximize number of words; ";
    print "3) Minimize number of words. "; 
    sys.exit(1); 

# Create directories
if not os.path.exists("out_" + str(version)):
	os.mkdir("out_" + str(version));
if not os.path.exists("log"): 
	os.mkdir("log");
if not os.path.exists("err_" + str(version)): 
	os.mkdir("err_" + str(version));     

# Create condor submit script
fout = open("djin-condor.submit", 'w');
fout.write("Universe = grid\n");
fout.write("grid_resource = pbs\n");
fout.write("batch_queue = guest\n"); 
fout.write("Executable = splitter\n"); 
fout.write("Log = log/job.log\n");
fout.write("Output = out_" + str(version) + "/job_$(Process).out\n");
fout.write("Error = err_"+ str(version) + "/job_$(Process).err\n");
fout.write("should_transfer_files = YES\n");  
fout.write("when_to_transfer_output = ON_EXIT\n");
fout.write("transfer_input_files = dict.txt\n"); 

# Read identifiers from input files 
inputDir = os.path.join(os.curdir, "input");
inputFilePath = os.path.join(inputDir, "WDM_identifiers3.csv"); 

cnt = 0; 

with open(inputFilePath, 'r') as fin:
    for line in fin: 
        if cnt < 1600: 
            line = line.rstrip('\n'); 
            line = line.rstrip('\n\r'); 
            fout.write("Arguments = \\\"" + line + "\\\" " + str(version) + '\n');  
            fout.write("Queue\n"); 
            cnt = cnt + 1; 
     
fout.close();  

# Submit condor job script 
a = datetime.now(); 
subprocess.call(["condor_submit", 'djin-condor.submit']);
subprocess.call(["condor_wait", "log/job.log"]); 
b = datetime.now(); 
c = b - a; 
print c.seconds;  # Print out time difference 

