A windows dll for be injected into other process. When dll loading, it should run the python script(default is door.py).

The default door.py use ipython kernel to create a ipython env.

Debug version could not run.

BUILD
- Install python. And pip install ipython, ipykernel, jupyter-console.
- Modify python.props.
- Copy pythonXX.dll to Release folder.
- Edit door.py for your own. 
- Copy pydoor.dll, pythonXX.dll, some vc runtime dlls and door.py to the diretory same with host process image file.
- Find a way to inject pydoor.dll to the host process.

NOTE
- The debug version could not running most cases, cause you don't have some python modules debug binaries.

