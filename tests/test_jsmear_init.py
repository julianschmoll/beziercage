"""Test initialization of jSmear in Maya."""
import unittest

from maya import cmds


class TestJsmearInit(unittest.TestCase):
    """Test Initialization of jSmear."""

    def test_init(self):
        """Test Initialization of jSmear."""
        cmds.loadPlugin("jSmear.mll")
