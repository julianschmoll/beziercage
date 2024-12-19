"""jSmear Menu."""
from maya import cmds
from maya import mel


ID = 0x0011580B


def create():
    """Creates jSmear Maya Menu."""
    destroy()
    for menu in ['mainDeformMenu', 'mainRigDeformationsMenu']:
        mel.eval(f'ChaDeformationsMenu MayaWindow|{menu};')
        items = cmds.menu(menu, q=True, ia=True)
        section = None
        for item in items:
            if cmds.menuItem(item, q=True, divider=True):
                section = cmds.menuItem(item, q=True, label=True)
            menu_label = cmds.menuItem(item, q=True, label=True)
            if menu_label == "Morph" and section == "Create":
                jsmear = cmds.menuItem(
                    label="jSmear",
                    command=_create_deformer,
                    insertAfter=item,
                    parent=menu,
                    annotation="Creates a jSmear Deformer on Current Selection with default options.",
                    data=ID
                )
                cmds.menuItem(
                    label="jSmearOptions",
                    command=_display_options,
                    insertAfter=jsmear,
                    parent=menu,
                    optionBox=True,
                    annotation="Opens Optioins Dialog for jSmear Deformer.",
                    data=ID
                )


def destroy():
    """Destroys jSmear Maya Menu"""
    for menu in ['mainDeformMenu', 'mainRigDeformationsMenu']:
        mel.eval('ChaDeformationsMenu MayaWindow|{0};'.format(menu))
        items = cmds.menu(menu, q=True, ia=True)
        for item in items:
            data =  cmds.menuItem(item, q=True, data=True)
            if data == ID:
                cmds.deleteUI(item, menuItem=True)


def _create_deformer(*args, **kwargs):
    pass


def _display_options(*args, **kwargs):
    pass
