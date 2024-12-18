"""Runner, running all unittests for jSmear."""
import sys
import maya.standalone
import unittest
from pathlib import Path
import os

def run_batch_tests():
    path = sys.argv[1]
    version = sys.argv[2]
    print(f"Appending {path}")
    sys.path.append(path)
    maya.standalone.initialize(name="python")
    root_path = Path(__file__).parent.parent
    test_path = Path(__file__).parent
    plug_in_path = Path(root_path / "build" / version / "plug-ins" )
    print(plug_in_path)
    os.environ["MAYA_PLUG_IN_PATH"] = plug_in_path
    suite = unittest.TestLoader().discover(test_path)
    runner = unittest.TextTestRunner(
        stream=sys.stdout,
        descriptions=True,
        verbosity=2
    )
    return runner.run(suite)

if __name__ == "__main__":
    run_batch_tests()
