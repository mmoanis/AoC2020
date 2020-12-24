import fileinput
from copy import deepcopy

seen = set()
for l in fileinput.input():
    # https://www.redblobgames.com/grids/hexagons/
    x, y, z, i = 0, 0, 0, 0
    while i < len(l):
        dx, dy, dz = 0, 0, 0
        if l[i] == 'e': dx, dy = 1, -1
        elif l[i] == 's':
            if l[i+1] == 'e': dy, dz = -1, 1
            else: dx, dz = -1, 1
            i += 1
        elif l[i] == 'n':
            if l[i+1] == 'w': dy, dz = 1, -1
            else: dx, dz = 1, -1
            i += 1
        else: dx, dy = -1, 1
        x, y, z = x + dx, y + dy, z + dz
        i += 1
    tile = tuple([x, y, z])
    seen.add(tile) if tile not in seen else seen.remove(tile)

print(len(seen))

def sim(tiles):
    ntiles = set()
    whites = {}
    deltas = [
        [0, 1, -1],
        [0, -1, 1],
        [1, 0, -1],
        [1, -1, 0],
        [-1, 0, 1],
        [-1, 1, 0]
    ]
    for tile in tiles:
        n = 0
        for d in deltas:
            dtile = tuple([tile[0]+d[0], tile[1]+d[1], tile[2]+d[2]])
            if dtile in tiles: n += 1
            if dtile in whites: whites[dtile] += 1
            else: whites[dtile] = 1
        if n != 0 and n <= 2: ntiles.add(tile) 
    for k,v in whites.items():
        if v == 2: ntiles.add(k) 
    return ntiles


for _ in range(0, 100):
    seen = sim(deepcopy(seen))

print(len(seen))
        
