import sys
sys.path.append("build/python_bindings")

import os
import numpy as np
import matplotlib.pyplot as plt

from odescppy import matrix, object_interface, solvers, systems


def exponential_system():
    a = 1.0
    system = systems.make_exponential_system(a)
    x0 = [1.0]
    return system, x0

def central_force_system():
    F = -0.1
    system = systems.make_central_force_system(F)
    x0 = [1.0, 0.0, 0.1, 0.5]
    return system, x0

def solve_system_euler(system, x0, t0, T, dt):

    euler_solver = solvers.make_euler_solver(dt)
    ode_result = solvers.solve_system(euler_solver, system, t0, x0, T)

    t, X = solvers.unpack_ode_results(ode_result)

    object_interface.object_delete(euler_solver)
    object_interface.object_delete(ode_result)

    return t, np.array(X)


if __name__ == "__main__":

    print(f"Process ID: {os.getpid()}")
    #input("Press Enter to continue...")

    system, x0 = central_force_system()
    
    t, X = solve_system_euler(system, x0, 0.0, 10.0, 1e-2)
    object_interface.object_delete(system)

    plt.plot(X[:, 0], X[:, 1])
    plt.legend()
    plt.show()

    print("Exiting...")