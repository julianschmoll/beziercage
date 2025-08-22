# Usage

Assuming you downloaded a build of cage or built it yourself and find this file in the root of the folder structure, this information is for you.

### Load Plugin in Maya

The Plugin can be added to Maya by setting the `MAYA_MODULLE_PATH` environment variable to the release folder of the bezier cage.
When starting Maya, the plugin can be loaded via the plugin manager UI or Maya cmds:

```python
from maya import cmds

# Loading the Cage Creator Tool
cmds.loadPlugin("cageCreator")

# Loading Cage Deformer
cmds.loadPlugin("cage")
```

### Applying the Deformer

To add a cage deformer to a rig or mesh, you can use the `Cage Tool`.
After loading the `cageCreator` plugin, the cage tool can be accessed via the Maya Deformer menu.
When the tool is invoked, you can simply click on the mesh to create a cage around it.
3 clicks form one patch. Make sure to click clock or counter-clockwise for correct patch creation.

If you want to invoke the context via Python or script with the plugins, here are some API examples:

```python
from maya import cmds

# calls cage creation context with specific cage name
context = cmds.cageCreationContext(name="cage_name")
cmds.setToolTo(context)

# adds the deformer to the current selection with the standard name
cmds.deformCage()

# adds deformer to specific objects with a specific name
cmds.deformCage(geometry_list, name="cage_name")

# triggers rebind of the deformer. this should be done when patches are added or removed
cmds.deformCage(name="cage_name", rebind=True)

# creates a offsetPin node
cmds.offsetPin(geometry, *objects_to_pin, name="pin_name")

# adds pin objects to an existing offsetPin node
cmds.offsetPin(geometry, *objects_to_pin, name="pin_name", append=True)
```
