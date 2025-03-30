"""Test initialization of cage in Maya."""
import unittest

from maya import cmds

from tests import decorators
try:
    import cage  # noqa: F401   # type: ignore
except ModuleNotFoundError:
    cage = None  # pylint: disable=invalid-name


PLUGIN = "cage.mll"


class TestcageLoading(unittest.TestCase):
    """Test Initialization of cage."""

    @decorators.plugin_loaded(PLUGIN)
    def test_load(self):
        """Initialize cage."""
        _check_plugin_state(loaded=True)

    @decorators.plugin_loaded(PLUGIN)
    def test_unload(self):
        """Uninitialize cage."""
        cmds.unloadPlugin(PLUGIN)
        _check_plugin_state(loaded=False)

    def test_cage_import(self):
        """Test importing cage."""
        assert cage, "Could not import cage python module."


def _check_plugin_state(loaded=True):
    plugin_loaded = cmds.pluginInfo(PLUGIN, query=True, loaded=True)
    assert loaded == plugin_loaded
