"""Decorators for tests."""
from maya import cmds


def plugin_loaded(plugin_name):
    """Decorator to load a plugin before running the decorated function.

    Args:
        plugin_name (str): Name of the plugin to load.
    """
    def decorator(func):
        def wrapper(*args, **kwargs):
            if not cmds.pluginInfo(plugin_name, query=True, loaded=True):
                cmds.loadPlugin(plugin_name)
            return func(*args, **kwargs)
        return wrapper
    return decorator
