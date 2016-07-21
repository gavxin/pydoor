import time
import sys

f = open('door.log', 'w')

f.write("Started...\n")
f.flush()

class Unbuffered(object):
   def __init__(self, stream):
       self.stream = stream
   def write(self, data):
       self.stream.write(data)
       self.stream.flush()
   def flush(self):
       self.stream.flush()
   def __getattr__(self, attr):
       return getattr(self.stream, attr)

sys.stdout = sys.stdin = sys.__stdout__ = Unbuffered(f)

import IPython
IPython.embed_kernel()

f.write("Stoped\n")
f.flush()

f.close()
