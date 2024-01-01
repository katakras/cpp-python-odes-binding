import numpy as np

def euler(system, t0, x0, T, dt):
    n_steps = int((T - t0) / dt + 1)

    x = np.zeros(shape=(n_steps + 1, len(x0)))
    x[0, :] = x0
    
    t = np.zeros(n_steps + 1)
    t[0] = t0

    for i in range(1, n_steps+1):
        x[i, :] = x[i-1, :] + dt * system.f(t0 + i * dt, x[i-1, :])
        t[i] = t0 + i * dt
    
    return t, x
    
