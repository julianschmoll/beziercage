"""Test initialization of jSmear in Maya."""
import unittest

from maya import cmds

from tests import decorators
try:
    import jsmear  # noqa: F401   # type: ignore
except ModuleNotFoundError:
    jsmear = None  # pylint: disable=invalid-name


PLUGIN = "jSmear.mll"


class TestJSmearLoading(unittest.TestCase):
    """Test Initialization of jSmear."""

    @decorators.plugin_loaded(PLUGIN)
    def test_load(self):
        """Initialize jSmear."""
        _check_plugin_state(loaded=True)

    @decorators.plugin_loaded(PLUGIN)
    def test_unload(self):
        """Uninitialize jSmear."""
        cmds.unloadPlugin(PLUGIN)
        _check_plugin_state(loaded=False)

    def test_jsmear_import(self):
        """Test importing jSmear."""
        assert jsmear, "Could not import jSmear python module."


def _check_plugin_state(loaded=True):
    plugin_loaded = cmds.pluginInfo(PLUGIN, query=True, loaded=True)
    assert loaded == plugin_loaded
