# jSmear Deformer

Maya Smear deformer.

## Usage

[//]: # (This part excluding introduction should stay up to date with data/USAGE.md)

You can either build the plugin yourself or download the corresponding build for your platform from the releases on GitHub.

### Load Plugin in Maya

To successfully load jSmear in Maya, add the `scripts` subdirectory to the `PYTHONPATH` (or `sys.path` in `userSetup.py`) and load the plugin either by adding the plug-ins path to the `MAYA_PLUG_IN_PATH` environment variable or loading it through the plugin manager UI from within Maya. If the scripts folder is not added correcty, the jSmear menu items won't be initialized.

### Applying the Deformer

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

## Building

1. Clone the repository.
2. Make sure cmake, maya and a c++ compiler is installed on your device.
3. Either run `build <MayaVersion>` (Windows) or `./build.sh <MayaVersion>` (other systems) in the root of the repository.

## Testing

After building, it is recommended to run automated unit tests by either running `test <MayaVersion>` on Windows or `./test.sh <MayaVersion>` on other systems. The unit tests use `mayapy` shipped with Maya. If Maya is installed in the default location, it will be picked up automatically; otherwise, it can be specified by adding `--mayapy /path/to/mayapy` to the test command.

## License 

Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.
