import numpy as np

class CentralForceSystem:

    def __init__(self, f):
        self._f = f

    def f(self, t, x):
        return np.array([x[2], x[3], self._f / (x[0] * x[0]), 0.0])

    def transform(self, x):
        for i in range(x.shape[0]):
            r = x[i, 0]
            cos_theta = np.cos(x[i, 1])
            sin_theta =  np.sin(x[i, 1])

            dr = x[i, 2]
            dtheta = x[i, 3]

            x[i, 0] = r * cos_theta
            x[i, 1] = r * sin_theta

            x[i, 2] = dr * cos_theta - r * dtheta * sin_theta
            x[i, 3] = dr * sin_theta + r * dtheta * cos_theta
        return x