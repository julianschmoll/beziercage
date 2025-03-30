"""cage Menu."""
from maya import cmds
from maya import mel


ID = 0x0011580B


def create():
    """Creates cage Maya Menu."""
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
                cage = cmds.menuItem(
                    label="cage",
                    command=_create_deformer,
                    insertAfter=item,
                    parent=menu,
                    annotation="Creates cage Deformer on Current Selection.",
                    data=ID
                )
                cmds.menuItem(
                    label="cageOptions",
                    command=_display_options,
                    insertAfter=cage,
                    parent=menu,
                    optionBox=True,
                    annotation="Opens Optioins Dialog for cage Deformer.",
                    data=ID
                )


def destroy():
    """Destroys cage Maya Menu"""
    for menu in ['mainDeformMenu', 'mainRigDeformationsMenu']:
        mel.eval(f'ChaDeformationsMenu MayaWindow|{menu};')
        items = cmds.menu(menu, q=True, ia=True)
        for item in items:
            data = cmds.menuItem(item, q=True, data=True)
            if data == ID:
                cmds.deleteUI(item, menuItem=True)


def _create_deformer(*args, **kwargs):  # pylint: disable=unused-argument
    # here we need to check saved option vars
    cmds.cage()


def _display_options(*args, **kwargs):  # pylint: disable=unused-argument
    cmds.confirmDialog(
        message="This is not yet implemented, sowwy :(",
        button=["okiu"]
    )
