"""Test initialization of jSmear in Maya."""
import unittest

from maya import cmds

class TestJsmearInit(unittest.TestCase):
    def test_init(self):
        cmds.loadPlugin()
