#!/usr/bin/env python
# encoding: latin1

import json

def store(file, list):
    with open(file, 'w') as fd:
        json.dump(list, fd, indent=4)


def load(file):
    with open(file, 'r') as fd:
        dist = json.load(fd)

    newdict = {}
    for key in dist.keys():
        newdict[key.encode("utf-8")] = getListByName(dist[key])
    return newdict

def getListByName(list):
    for i in range(len(list)):
        sublist = list[i]
        for j in range(len(sublist)):
            list[i][j] = list[i][j].encode("utf-8")
    return list

def appendToList(file, listname, newString, index):
    dict = load(file)

    dict[listname][index].append(newString)
    store(file, dict)



basicData = {   'classe0' : [["hola"], ["cómo te llamas"],["qué hora es"],["qué tiempo hace", "va a llover hoy"]],
                'classe1' : [["buenas noches","apaga la luz"],["baja la persiana"]],
                'classe2' : [["pet"]],
                'classe3' : [["pis"]]   }

store("test.json", basicData)
