"""Test initialization of jSmear in Maya."""
import unittest

from maya import cmds


PLUGIN = "jSmear.mll"

class TestJsmearInit(unittest.TestCase):
    """Test Initialization of jSmear."""

    def test_init(self):
        """Test Initialization of jSmear."""
        cmds.loadPlugin(PLUGIN)
        _check_plugin_state(loaded=True)
        cmds.unloadPlugin(PLUGIN)
        _check_plugin_state(loaded=False)


def _check_plugin_state(loaded=True):
    plugin_loaded = cmds.pluginInfo(PLUGIN, query=True, loaded=True)
    assert loaded == plugin_loaded
