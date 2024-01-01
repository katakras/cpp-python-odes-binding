import ctypes

import os
import matplotlib.pyplot as plt

import cpp_interface
from cpp_interface import C_LIB

from replication.odes import euler
from replication.systems import CentralForceSystem


def exponential_system():
    system_ptr = C_LIB.make_ExponentialSystem(ctypes.c_double(1.0))
    x0 = cpp_interface.vector_wrap([1.0])
    return system_ptr, None, x0, lambda ptr : C_LIB.delete_ExponentialSystem(ptr)

def central_force_system():
    F = -0.1
    x0 = [1.0, 0.0, 0.1, 0.5]
    system_ptr = C_LIB.make_CentralForceSystem(ctypes.c_double(F))
    x0_ptr = cpp_interface.vector_wrap(x0)
    return system_ptr, CentralForceSystem(F), x0, x0_ptr, lambda ptr : C_LIB.delete_CentralForceSystem(ptr) 

def solve_system_euler(system_ptr, system_py, x0, x0_ptr, t0, T, dt):
    ode_result = C_LIB.euler(system_ptr, ctypes.c_double(t0), x0_ptr, ctypes.c_double(T), ctypes.c_double(dt))

    t_ptr = C_LIB.ODEResults_t_address(ode_result)
    t_cpp = cpp_interface.vector_unwrap(t_ptr)    

    m_ptr = C_LIB.ODEResults_m_address(ode_result)
    x_cpp = cpp_interface.matrix_unrwap(m_ptr)

    C_LIB.delete_ODEResults(ode_result)

    t_py, x_py = euler(system_py, t0, x0, T, dt)
    x_py = system_py.transform(x_py)

    return t_cpp, x_cpp, t_py, x_py


if __name__ == "__main__":

    print(f"Process ID: {os.getpid()}")
    #input("Press Enter to continue...")

    system_ptr, system_py, x0, x0_ptr, del_func = central_force_system()
    
    t_cpp, x_cpp, t_py, x_py = solve_system_euler(system_ptr, system_py, x0, x0_ptr, 0.0, 10.0, 1e-2)
    del_func(system_ptr)


    plt.plot(x_cpp[:, 0], x_cpp[:, 1], label="CPP")
    plt.plot(x_py[:, 0], x_py[:, 1], label="Python")
    plt.legend()
    plt.show()

    print("Exiting...")