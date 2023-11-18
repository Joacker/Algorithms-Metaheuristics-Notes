from sdaopt import sda
def rosenbrock(x):
    return(100 * (x[1]-x[0] ** 2) ** 2 + (1 - x[0]) ** 2) 

ret = sda(rosenbrock, None, [(-30, 30)] * 2)

print("global minimum:\nxmin = {0}\nf(xmin) = {1}".format(
    ret.x, ret.fun))