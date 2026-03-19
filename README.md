# Bezier Cage Deformer

This is a Bezier Cage Deformer for Autodesk Maya written for my bachelors thesis. It was inspired by Pixars Curvenet.
This plugin contains Tools for cage generation as well as the deformer itself and a custom UV-Pin like Node.

Here is a short demo of the cage deformer in Maya (might take some time to load):
![bezier_cage.gif](data/bezier_cage.gif)

Please use in production at your own risk!

## Usage

[//]: # (This part excluding introduction should stay up to date with data/USAGE.md)

You can either [build the plugin yourself](#building) or download the corresponding build for your platform from the releases on GitHub.

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

To add a cage deformer to a rig or mesh, you can use the `Cage Tool`. This requires numpy being available in the Maya Python environment.
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

## Building

1. Clone the repository.
2. Make sure cmake and a c++ compiler are installed on your device.
3. Make sure Maya Headers (necessary for compiling) can be found by [findMaya.cmake](modules/findMaya.cmake). 
4. Either run `build <MayaVersion>` (Windows) or `./build.sh <MayaVersion>` (other systems) in the root of the repository.

## Testing

After building, it is recommended to run automated unit tests by either running `test <MayaVersion>` on Windows or `./test.sh <MayaVersion>` on other systems. The unit tests use `mayapy` shipped with Maya. If Maya is installed in the default location, it will be picked up automatically; otherwise, it can be specified by adding `--mayapy /path/to/mayapy` to the test command.

# Known Issues
- Maya seems to crash on Linux when opening a scene with more than one cage being applied.
