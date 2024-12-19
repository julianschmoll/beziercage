"""Test initialization of jSmear in Maya."""
import unittest

from maya import cmds


PLUGIN = "jSmear.mll"


class TestJSmearLoading(unittest.TestCase):
    """Test Initialization of jSmear."""

    def test_load(self):
        """Initialize jSmear."""
        cmds.loadPlugin(PLUGIN)
        _check_plugin_state(loaded=True)

    def test_unload(self):
        """Uninitialize jSmear."""
        cmds.unloadPlugin(PLUGIN)
        _check_plugin_state(loaded=False)


def _check_plugin_state(loaded=True):
    plugin_loaded = cmds.pluginInfo(PLUGIN, query=True, loaded=True)
    assert loaded == plugin_loaded
