"""Runner, running all unittests for cage."""
import os
from pathlib import Path
import sys
import unittest
import logging

from maya import cmds
import maya.standalone
import maya.app.commands


orig_process_command_list = maya.app.commands.processCommandList


def run_batch_tests():
    """Runs all configured tests."""
    _setup_environment()
    test_path = Path(__file__).parent
    suite = unittest.TestLoader().discover(str(test_path))
    runner = unittest.TextTestRunner(
        stream=sys.stdout,
        descriptions=True,
        verbosity=2
    )
    return runner.run(suite)


def _setup_environment():
    root_path = sys.argv[1]
    version = sys.argv[2]

    module_path = Path(root_path, "build", version)

    if not module_path.exists():
        print("Please build the Plugin before testing!")
        print(f"Expected build path was: {module_path}")
        sys.exit(1)

    os.environ["MAYA_MODULE_PATH"] = str(module_path)
    os.environ["MTOA_STARTUP_LOG_VERBOSITY"] = str(0)

    maya.app.commands.processCommandList = _set_option_vars
    maya.standalone.initialize(name="python")


def _set_option_vars():
    orig_process_command_list()
    cmds.optionVar(iv=("SafeModeExecUserSetupScript", 0))
    cmds.optionVar(iv=("TrustCenterPathOption", 0))


if __name__ == "__main__":
    run_batch_tests()
