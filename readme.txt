Pydoor

Pydoor is a backdoor dll included python environment. When pydoor.dll loaded by some process, it will run the `door.py` python script in the same directory. 

The default door.py use ipython kernel to create a ipython env. You can remote connect to the ipython kernel, and running some python code you want.

Debug version could not run.

Prepare and Build
- Install python. And pip install ipython, ipykernel, jupyter-console.
  - Choose 32 bit or 64 bit python same as the process that you want to inject.
  - The ipython, ipykernel, jupyter-console is not necessary, but if you want to use the default door.py, you should install it. 
- Modify python.props.
  - Modify the path string C:\Python37-32 and C:\Python37 to your python install location. 
  - If you only want 32bit version, ignore x64 path.
- Build the solution.

Usage
- Copy pydoor.dll, pythonXX.dll, some vc runtime dlls and door.py to the diretory same with host process image file.
- Find a way to inject pydoor.dll to the host process.
- Dbgview.exe (You can found in Sysinternals Suite) can view log message.

NOTE
- The debug version could not running most cases, because don't have debug binaries for some python modules.

About default door.py

The default door.py start an embedded ipython kernel. When you successfully injected dll, you can run command `ipython console --existing` to connect pydoor.

> The ipython environment created by `IPython.embed_kernel()` is very strange, has some variable scoping issue ...


中文简介

简单说，这个 dll 就是用来注入到别的进程，会创建新的线程并运行同目录下的 door.py 。

后记：这个 pydoor 个人一直觉得比较鸡肋，感觉没啥用，直到……



