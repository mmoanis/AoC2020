import fileinput
import re
from copy import deepcopy

def score(cards):
    print(sum(cards[i]*(len(cards)-i) for i in range(len(cards))))


def game1(cards1, cards2):
    while len(cards1) > 0 and len(cards2) > 0:
        if cards1[0] > cards2[0]:
            cards1.append(cards1[0])
            cards1.append(cards2[0])
        elif cards1[0] < cards2[0]:
            cards2.append(cards2[0])
            cards2.append(cards1[0])
        cards1.pop(0)
        cards2.pop(0)

    cards = cards1 if len(cards1) > 0 else cards2
    score(cards)


def game2(cards1, cards2):
    seen1, seen2 = set(), set()
    while len(cards1) > 0 and len(cards2) > 0:
        if str(cards1) in seen1 or str(cards2) in seen2:
            return True
        
        seen1.add(str(cards1))
        seen2.add(str(cards2))

        if len(cards1) > cards1[0] and len(cards2) > cards2[0]:
            p1 = game2(cards1[1:cards1[0]+1], cards2[1:cards2[0]+1])
        else: p1 = cards1[0] > cards2[0]

        if p1:
            cards1.append(cards1[0])
            cards1.append(cards2[0])
        else:
            cards2.append(cards2[0])
            cards2.append(cards1[0])
        cards1.pop(0)
        cards2.pop(0)
    return len(cards1) > len(cards2)

Lines = list([l.strip() for l in fileinput.input()])
cards1, cards2 = [], []
cards = cards1
for l in Lines:
    if 'Player 1:' in l: continue
    elif 'Player 2:' in l:
        cards = cards2
    elif l:
        cards.append(int(l))


game1(cards1[:], cards2[:])
game2(cards1, cards2)
score(cards1)
score(cards2)
