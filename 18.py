
import sys

def gb(e):
    # print(e)
    br = 0
    for i in range(len(e)):
        if e[i] == '(': br+=1
        elif e[i] == ')': br-=1
        if br==0: return i
    return 0

def ev(e, ind):
    if len(e) == 0 or not e: return 0

    i, left = 0, 0
    while i < len(e):
        if e[i] == '(':
            j = gb(e[i:]) + i
            left += ev(e[i+1:j], ind + " ")
            i = j + 1
        elif e[i] == '+' or e[i] == '*':
            k = i + 1
            if e[k] == '(':
                j = gb(e[k:]) + i
                right = ev(e[k+1:j+1], ind + " ")
            else:
                right = int(e[k])
                j = i
            left = left + right if e[i] == '+' else left * right
            i = j + 2
        else:
            left += int(e[i])
            i = i + 1
    return left

def ev2(e, ind):
    # print('{}{}'.format(ind, e))
    if len(e) == 0 or not e: return 0
    elif len(e) == 1 and e[0].isdigit(): return int(e[0])

    i, left = 0, 0
    while i < len(e):
        if e[i] == '(':
            j = gb(e[i:]) + i
            left += ev2(e[i+1:j], ind + ' ')
            i = j + 1
        elif e[i] == '*':
            right = ev2(e[i+1:], ind + ' ')
            left = left * right
            return left
        elif e[i] == '+':
            k = i + 1
            if e[k] == '(':
                j = gb(e[k:]) + i
                right = ev2(e[k+1:j+1], ind + ' ')
            else:
                right = int(e[k])
                j = i
            left = left + right
            i = j + 2
        else:
            left += int(e[i])
            i = i + 1
    return left

sum1, sum2 = 0, 0
expr = []
for line in sys.stdin:
    exp = []
    for c in line:
        if c != ' ' and c != '\n':
            exp.append(c)
    expr+= [exp]
    sum1 += ev(exp, '')
    sum2 += ev2(exp, '')

print(sum1)
print(sum2)


