"""Decorators for tests."""
from maya import cmds


def plugin_loaded(plugin_names):
    """Decorator to load a plugin before running the decorated function.

    Args:
        plugin_names (str or list): Name of the plugins to load.
    """
    def decorator(func):
        def wrapper(*args, **kwargs):
            if isinstance(plugin_names, str):
                plugins = [plugin_names]
            else:
                plugins = plugin_names
            for plugin in plugins:
                if not cmds.pluginInfo(plugin, query=True, loaded=True):
                    cmds.loadPlugin(plugin)
            return func(*args, **kwargs)
        return wrapper
    return decorator


def clean_scene():
    """Decorator to clean the scene before running the decorated function."""
    def decorator(func):
        def wrapper(*args, **kwargs):
            cmds.file(new=True, force=True)
            return func(*args, **kwargs)
        return wrapper
    return decorator
