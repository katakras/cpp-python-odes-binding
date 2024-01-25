import sys
sys.path.append("build/python_bindings")

from odescppy import matrix, object_interface, solvers, systems

m1 = matrix.python_array_to_matrix([[1.0, 2.0], [5.0, 4.0]])
print(m1)

m2 = matrix.python_array_to_matrix([[0.0]])
print(m2)

print(object_interface.object_list())

print(object_interface.object_delete(m2))
print(object_interface.object_delete(m2))

print(matrix.matrix_to_python_array(m1))
print(matrix.matrix_to_python_array(m1))


F = -0.1
x0 = [1.0, 0.0, 0.1, 0.5]

dt = 0.1

euler_solver = solvers.make_euler_solver(0.1)
exponential_system = systems.make_exponential_system(1.0)

system_solution = solvers.solve_system(euler_solver, exponential_system, 0.0, [1.0], 1.0)
print(system_solution)

t, X = solvers.unpack_ode_results(system_solution)

print(t)
print(X)
