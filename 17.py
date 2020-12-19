import sys
import copy


def generate_space_3d():
    z, x, y = 0, 0 ,0

    space = dict()
    space[str(z)] = dict()

    for line in sys.stdin:
        space[str(z)][str(x)] = dict()
        y = 0
        for c in line:
            if c == '#':
                space[str(z)][str(x)][str(y)] = 0
            y += 1 
        x += 1

    print(space)
    return space

def generate_space_4d():
    z, w, x, y = 0, 0 ,0, 0

    space = dict()
    space[str(z)] = dict()
    space[str(z)][str(w)] = dict()

    for line in sys.stdin:
        space[str(z)][str(w)][str(x)] = dict()
        y = 0
        for c in line:
            if c == '#':
                space[str(z)][str(w)][str(x)][str(y)] = 0
            y += 1 
        x += 1

    print(space)
    return space


def neighbours_3d(space, nspace, kz, kx, ky):
    count = 0
    for dz in range(-1, 2):
        z = str(int(kz) + dz)
        for dx in range(-1, 2):
            x = str(int(kx) + dx)
            for dy in range(-1, 2):
                y = str(int(ky) + dy)
                if z == kz and y == ky and x == kx: continue
                if z in space and x in space[z] and y in space[z][x]:
                    count += 1
                
                # Mark my neighbours
                if not z in nspace: nspace[z] = dict()
                if not x in nspace[z]: nspace[z][x] = dict()
                if not y in nspace[z][x]: nspace[z][x][y] = 0
                nspace[z][x][y] += 1

    return count, nspace

def neighbours_4d(space, nspace, kz, kw, kx, ky):
    count = 0
    for dz in range(-1, 2):
        z = str(int(kz) + dz)
        for dw in range(-1, 2):
            w = str(int(kw) + dw)
            for dx in range(-1, 2):
                x = str(int(kx) + dx)
                for dy in range(-1, 2):
                    y = str(int(ky) + dy)
                    if z == kz and w == kw and y == ky and x == kx: continue
                    if z in space and w in space[z] and x in space[z][w] and y in space[z][w][x]:
                        count += 1
                    
                    # Mark my neighbours
                    if not z in nspace: nspace[z] = dict()
                    if not w in nspace[z]: nspace[z][w] = dict()
                    if not x in nspace[z][w]: nspace[z][w][x] = dict()
                    if not y in nspace[z][w][x]: nspace[z][w][x][y] = 0
                    nspace[z][w][x][y] += 1

    return count, nspace

def cycle_3d(space):
    ''' One cycle simulation'''

    lspace = copy.deepcopy(space)
    nspace = copy.deepcopy(space)

    # Check active
    for kz in space:
        for kx in space[kz]:
            for ky in space[kz][kx]:
                count, nspace = neighbours_3d(space, nspace, kz, kx, ky)
                if count != 2 and count != 3:
                    del lspace[kz][kx][ky]
    
    # Convert to active
    for kz in nspace:
        for kx in nspace[kz]:
            for ky in nspace[kz][kx]:
                if nspace[kz][kx][ky] == 3:
                    if not kz in lspace: lspace[kz] = dict()
                    if not kx in lspace[kz]: lspace[kz][kx] = dict()
                    lspace[kz][kx][ky] = 0
    
    return lspace

def cycle_4d(space):
    ''' One cycle simulation'''

    lspace = copy.deepcopy(space)
    nspace = copy.deepcopy(space)

    # Check active
    for kz in space:
        for kw in space[kz]:
            for kx in space[kz][kw]:
                for ky in space[kz][kw][kx]:
                    count, nspace = neighbours_4d(space, nspace, kz, kw, kx, ky)
                    if count != 2 and count != 3:
                        del lspace[kz][kw][kx][ky]
    
    # Convert to active
    for kz in nspace:
        for kw in nspace[kz]:
            for kx in nspace[kz][kw]:
                for ky in nspace[kz][kw][kx]:
                    if nspace[kz][kw][kx][ky] == 3:
                        if not kz in lspace: lspace[kz] = dict()
                        if not kw in lspace[kz]: lspace[kz][kw] = dict()
                        if not kx in lspace[kz][kw]: lspace[kz][kw][kx] = dict()
                        lspace[kz][kw][kx][ky] = 0
    
    return lspace

# Part 1
# space = generate_space_3d()
# for _ in range(0, 6):
#     space = cycle_3d(space)

# count = 0
# for kz in space:
#     for kx in space[kz]:
#         for ky in space[kz][kx]:
#             count += 1

# print(count)

# Part 2
space = generate_space_4d()
for _ in range(0, 6):
    space = cycle_4d(space)

count = 0
for kz in space:
    for kw in space[kz]:
        for kx in space[kz][kw]:
            for ky in space[kz][kw][kx]:
                count += 1

print(count)
