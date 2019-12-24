import itertools
import bpy

walls = ['WallRight', 'WallUp', 'WallLeft', 'WallDown']

for bools in itertools.product([True, False], repeat=4):
    walls_to_hide = [wall for (i,wall) in enumerate(walls) if not bools[i]]
    for wall in walls:
        bpy.data.objects[wall].hide_render = False
    for wall in walls_to_hide:
        bpy.data.objects[wall].hide_render = True
    suffix = ''.join(str(int(b)) for b in bools)
    bpy.context.scene.render.filepath = '../maze-tile%s' % suffix
    bpy.ops.render.render(write_still=True)
