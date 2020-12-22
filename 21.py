import fileinput

Lines = list([l.strip() for l in fileinput.input()])
ingreds = {}
allergs = {}
for l in Lines:
    items = l.split(' ')
    ll = []
    for item in items:
        if '(contains' in item: continue
        elif ',' in item or ')' in item:
            allergy = item[:-1]
            if allergy in allergs:
                foods = allergs[allergy][:]
                for food in allergs[allergy]:
                    if food not in ll:
                        foods.remove(food)
                allergs[allergy] = foods
            else:
                allergs[allergy] = ll
        else:
            ll.append(item)
            if item in ingreds: ingreds[item]+=1
            else: ingreds[item] = 1

todo = allergs.keys()
while True:
    skip = True
    for k,v in allergs.items():
        if k in todo and len(v) == 1:
            skip = False
            K, V = k, v[0]
            todo.remove(k)
            break
    
    if skip: break

    for k in allergs.keys():
        if k == K: continue
        if V in allergs[k]:
            allergs[k].remove(V)

ident = set()
for k, v in allergs.items():
    for vv in v: ident.add(vv)

ans = 0
for k,v in ingreds.items():
    if k not in ident:
        ans += v

print(ans)

#Part 2
ans = ''
sortedK = sorted(allergs.keys())
for k in sortedK:
    ans += ''.join(allergs[k]) + ','

print(ans[:-1])
