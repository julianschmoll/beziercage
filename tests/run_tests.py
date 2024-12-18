"""Runner, running all unittests for jSmear."""
import os
from pathlib import Path
import sys
import unittest

import maya.standalone


def run_batch_tests():
    """Runs all configured tests."""
    _setup_environment()
    test_path = Path(__file__).parent
    suite = unittest.TestLoader().discover(test_path)
    runner = unittest.TextTestRunner(
        stream=sys.stdout,
        descriptions=True,
        verbosity=2
    )
    return runner.run(suite)


def _setup_environment():
    path = sys.argv[1]
    version = sys.argv[2]
    sys.path.append(path)
    root_path = Path(__file__).parent.parent
    plug_in_path = Path(root_path / "build" / version / "jSmear" / "plug-ins")
    os.environ["MAYA_PLUG_IN_PATH"] = str(plug_in_path)
    maya.standalone.initialize(name="python")


if __name__ == "__main__":
    run_batch_tests()
