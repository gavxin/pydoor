Pydoor

Pydoor is a backdoor dll included python environment. When pydoor.dll loaded by some process, it will run the `door.py` python script in the same directory. 

The default door.py use ipython kernel to create a ipython env. You can remote connect to the ipython kernel, and running some python code you want.

Debug version could not run.

BUILD AND RUN
- Install python. And pip install ipython, ipykernel, jupyter-console.
- Modify python.props.
- Build the solution.
- Copy pythonXX.dll to Release folder.
- Edit door.py for your own. 
- Copy pydoor.dll, pythonXX.dll, some vc runtime dlls and door.py to the diretory same with host process image file.
- Find a way to inject pydoor.dll to the host process.

NOTE
- The debug version could not running most cases, because don't have debug binaries for some python modules.

