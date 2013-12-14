#!/usr/bin/python

import subprocess; 
import sys; 
import os; 
from datetime import datetime; 

# Submit condor job script 
a = datetime.now(); 
subprocess.call(["condor_submit", 'serial.submit']);
subprocess.call(["condor_wait", "job_serial.log"]); 
b = datetime.now(); 
c = b - a; 
print c.seconds;  # Print out time difference 

