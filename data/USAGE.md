# Usage

You can either build the plugin yourself or download the correct build for your platform from the releases.

## Load Plugin in Maya

To successfully load jSmear in Maya, add the `scripts` subdirectory to the `PYTHONPATH` (or `sys.path` in `userSetup.py`) and load the plugin either by adding the plug-ins path to the `MAYA_PLUG_IN_PATH` environment variable or loading it through the plugin manager UI from within Maya.

## Applying the Deformer

The deformer can either be added via the menu or with the following Python command:

```python
from maya import cmds

# Apply the deformer to the current selection with the standard name
cmds.jSmear()

# Apply to specific objects with a specific name
cmds.jSmear("object1", "object2", name="Schmiererei")

# To query all available flags, use
cmds.jSmear(help=True)
```
