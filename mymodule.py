import numpy

def array_tutorial(a):
    print("array_tutorial - python")
    print(a)
    print("")
    firstRow = a[0,:]
    #beta = numpy.array([[10,20,30],[10,20,30],[10,20,30]])
    #firstRow = beta[0,:]
    return firstRow

def myfunction():
    beta = numpy.array([[1,2,3],[1,2,3],[1,2,3]])
    print("myfunction - python")
    print(beta)
    print("")
    firstRow = beta[0,:]
    return firstRow