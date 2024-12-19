"""jSmear Menu."""
from maya import cmds
from maya import mel


MENU_ITEMS = []
INSERT_AFTER = "Morph"


def create():
    """Creates jSmear Maya Menu."""
    global MENU_ITEMS
    section = None

    if MENU_ITEMS:
        return
    for menu in ['mainDeformMenu', 'mainRigDeformationsMenu']:
        mel.eval(f'ChaDeformationsMenu MayaWindow|{menu};')
        items = cmds.menu(menu, q=True, ia=True)
        for item in items:
            if cmds.menuItem(item, q=True, divider=True):
                section = cmds.menuItem(item, q=True, label=True)
            menu_label = cmds.menuItem(item, q=True, label=True)
            if menu_label == INSERT_AFTER and section == 'Create':
                jsmear = cmds.menuItem(
                    label="jSmear", command=_create_deformer, sourceType='python', insertAfter=item, parent=menu
                )
                jsmear_options = cmds.menuItem(
                    command=_display_options, insertAfter=cvwrap_item, parent=menu, optionBox=True
                )
                MENU_ITEMS.append(jsmear)
                MENU_ITEMS.append(jsmear_options)


def destroy():
    """Destroys jSmear Maya Menu"""
    global MENU_ITEMS
    for item in MENU_ITEMS:
        cmds.deleteUI(item, menuItem=True)
    MENU_ITEMS = []


def _create_deformer():
    pass


def _display_options():
    pass
