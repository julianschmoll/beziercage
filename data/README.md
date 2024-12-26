# Load Plugin in Maya

To successfully load jSmear in Maya, add scripts subdirectory as a PYTHONPATH (or `sys.path` in `userSetup.py`) and load Plugin either by adding plug-ins path to `MAYA_PLUG_IN_PATH` env variable or loading it through plugin manager UI from within Maya.

# Usage in Maya

Deformer can either be added via menu or with python command

```python
from maya import cmds

cmds.jSmear()
```
