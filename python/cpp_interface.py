import ctypes
import pathlib
import os
import re

import numpy as np

libname = pathlib.Path().absolute() / "build" / "libCPPyODEs.dylib"
C_LIB = ctypes.CDLL(libname) 

_cpp_src_source_dir = pathlib.Path().absolute() / "cpp"

# Map of C++ types to ctypes type
_types_map = {
    "void": "None",
    "double": "c_double",
    "size_t": "c_size_t",
    "int": "c_int"
}

# Converts a C++ type as a string to a ctypes type as a string. By default, anything not recognized in the map
# (mainly pointers) is converted to ctypes.c_void_p
def _convert_type_to_ctypes_alias(type_str):
    if type_str == "void":
        return "None"
    elif type_str in _types_map:
        return "ctypes." + _types_map[type_str]
    else:
        return "ctypes.c_void_p"

# Iterates a list of comma-separated C++ input arguments
def _parse_input_arguments_iter(arguments):
    while "," in arguments:
        separator_index = arguments.index(",")
        while arguments[:separator_index].count("<") != arguments[:separator_index].count(">"):
            separator_index = arguments.index(",", separator_index)
        argument = arguments[:separator_index]
        arguments = arguments[separator_index+1:]
        yield argument
    yield arguments

# Returns the C++ type of an input argument
def _get_type_from_argument(argument):
    arg_match = re.match("[ ]*(const |)(?P<TYPE>.*) [\w]+", argument)
    if arg_match is None:
        raise Exception("Didn't match any argument type.")
    return arg_match.group("TYPE")

def _transform_types_and_join(arguments):
    return ",".join(arguments)

# Parses a header file, looking for the tag "EXPORT_FUNCTION" and registering functions in the ctypes interface layer
# by checking the input/output types
def _parse_file(file_path):
    with open(file_path) as f_o:
        for line in f_o:
            if "EXPORT_FUNCTION" in line:
                match = re.search("[ ]*EXPORT_FUNCTION[ ]*(?P<RETURN_TYPE>[\w:<>* ]+)[ ]+(?P<FUNCTION_NAME>[\w]+)\((?P<ARGUMENTS>.*)\)", line)
                if match is not None:
                    function_name = match.group("FUNCTION_NAME")
                    return_type = match.group("RETURN_TYPE")
                    exec(f"C_LIB.{function_name}.restype = {_convert_type_to_ctypes_alias(return_type)}")
                    #print(f"C_LIB.{function_name}.restype = {_convert_type_to_ctypes_alias(return_type)}")

                    arguments = match.group("ARGUMENTS")
                    arguments = [_get_type_from_argument(a) for a in _parse_input_arguments_iter(arguments)]
                    arguments = [_convert_type_to_ctypes_alias(a) for a in arguments]
                    exec(f"C_LIB.{function_name}.argtypes = [{_transform_types_and_join(arguments)}]")
                    #print(f"C_LIB.{function_name}.argtypes = [{_transform_types_and_join(arguments)}]")
                    print(f"Registered {function_name}")


def _recurse_and_parse_folder(folder, file_exclusions):
    for file in os.listdir(folder):
        file_path = os.path.join(folder, file)
        if os.path.isdir(file_path):
            _recurse_and_parse_folder(file_path, file_exclusions)
        elif ".hpp" in file and file not in file_exclusions:
            _parse_file(file_path)

exclusions = ["macros.hpp"]
_recurse_and_parse_folder(_cpp_src_source_dir, exclusions)

def matrix_unrwap(c_type_v_ptr):
    n_rows = C_LIB.get_matrix_n_rows(c_type_v_ptr)
    n_cols = C_LIB.get_matrix_n_cols(c_type_v_ptr)

    ret = np.zeros((n_rows, n_cols))

    for i_row in range(n_rows):
        for i_col in range(n_cols):
            ret[i_row, i_col] = C_LIB.get_matrix_element(c_type_v_ptr, ctypes.c_size_t(i_row), ctypes.c_size_t(i_col))
    return ret

def vector_unwrap(c_type_v_ptr):
    vector_size = C_LIB.vector_size(c_type_v_ptr)
    v = np.array([C_LIB.vector_get(c_type_v_ptr, i) for i in range(vector_size)])
    return v

def vector_wrap(v):
    v_ptr = C_LIB.make_vector(ctypes.c_size_t(len(v)), ctypes.c_double(0.0))
    for i in range(len(v)):
        C_LIB.vector_set(v_ptr, ctypes.c_double(v[i]), ctypes.c_size_t(i))
    return v_ptr
