"""cage Menu."""
from maya import cmds
from maya import mel


# We use this id to identify the cage menu items.
ID = 0x0011580B


def create():
    """Creates cage Maya Menu."""
    destroy()
    for menu in ['mainDeformMenu', 'mainRigDeformationsMenu']:
        mel.eval(f'ChaDeformationsMenu MayaWindow|{menu};')
        items = cmds.menu(menu, q=True, ia=True)
        for item in items:
            menu_label = cmds.menuItem(item, q=True, label=True)
            if menu_label == "softModDialogItem":
                cage = cmds.menuItem(
                    label="Cage Tool",
                    command=_enter_tool_context,
                    insertAfter=item,
                    parent=menu,
                    annotation="Creates cage Deformer on Current Selection.",
                    data=ID,
                    image="creation_context_32.png"
                )
                cmds.menuItem(
                    label="cageToolOptions",
                    command=_display_options,
                    insertAfter=cage,
                    parent=menu,
                    optionBox=True,
                    annotation="Opens Options Dialog for cage Deformer.",
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


def _enter_tool_context(*args, **kwargs):  # pylint: disable=unused-argument
    cage_creator_ctx = cmds.cageCreationContext()
    cmds.setToolTo(cage_creator_ctx)


def _display_options(*args, **kwargs):  # pylint: disable=unused-argument
    cmds.confirmDialog(
        message="This is not yet implemented, sowwy :(",
        button=["Okiu"]
    )
