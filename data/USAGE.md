# Usage

Assuming you downloaded a build of jSmear or built it yourself and find this file in the root of the folder structure, this information is for you.

## Load Plugin in Maya

To successfully load jSmear in Maya, add the `scripts` subdirectory to the `PYTHONPATH` (or `sys.path` in `userSetup.py`) and load the plugin either by adding the plug-ins path to the `MAYA_PLUG_IN_PATH` environment variable or loading it through the plugin manager UI from within Maya. If the scripts folder is not added correcty, the jSmear menu items won't be initialized.

## Applying the Deformer

The deformer can either be added via the menu item or with the following Python command:

```python
from maya import cmds

# Apply the deformer to the current selection with the standard name
cmds.jSmear()

# Apply to specific objects with a specific name
cmds.jSmear("object1", "object2", name="Schmiererei")

# To query all available flags, use
cmds.jSmear(help=True)
```
