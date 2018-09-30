import time
import sys
import logging
import ctypes
import traceback

OutputDebugString = ctypes.windll.kernel32.OutputDebugStringW
#OutputDebugString.argtypes = [ctypes.c_char_p]
  
class DbgViewHandler(logging.Handler):
  def __init__(self):
    logging.Handler.__init__(self)
        
  def emit(self, record):
    OutputDebugString(self.format(record))

logger = logging.getLogger("pydoor")
def init_logger():
  logger.setLevel(logging.DEBUG)
  ch = DbgViewHandler()
  ch.setLevel(logging.DEBUG)
  formatter = logging.Formatter("%(asctime) -25s [%(thread) 5s] %(levelname) -8s %(name) -25s %(message)s")
  ch.setFormatter(formatter)
  logger.addHandler(ch)

class InfoStreamToLogger(object):
  def write(self, data):
    logger.info(data)
  def flush(self):
    pass

class ErrorStreamToLogger(object):
  def write(self, data):
    logger.error(data)
  def flush(self):
    pass

sys.stdout = sys.__stdout__ = InfoStreamToLogger()
sys.stderr = sys.__stderr__ = ErrorStreamToLogger()

def main():
  init_logger()
  try:
    logger.info("door.py started, embed_kernel...")

    import IPython
    IPython.embed_kernel()
    logger.info("door.py end.")
  except Exception as e:
    err = traceback.format_exc()
    logger.error("Exception!\n" + err)
  
if __name__ == "__main__":
  main()


    

