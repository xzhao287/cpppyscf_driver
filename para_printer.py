from pyscf import scf, dft


def printQMCoords(pQMCoords):
    return 123.456789012345, pQMCoords

def printQMKinds(pQMKinds):
    print(pQMKinds)
    return pQMKinds

def printQMSystem(pQMCoords, pQMKinds, pQMMethods, pQMMult, pQMCharge):
    print(pQMKinds)
    print(pQMCoords)
    print(pQMMethods)
    print(pQMMult)
    print(pQMCharge)
    return pQMCoords, pQMKinds

def QMcalculation(pQMCoords, pQMKinds, pQMMethods, pQMMult, pQMCharge):
    
    return Energy