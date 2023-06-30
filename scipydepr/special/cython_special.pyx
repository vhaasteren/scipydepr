cimport numpy as np
import numpy as np
np.import_array()

import cython

cdef extern from "special.c":
    double onef2(
            double a,
            double b,
            double c,
            double x,
            double *err)

cdef extern from "special.c":
    double threef0(
            double a,
            double b,
            double c,
            double x,
            double *err)

@cython.boundscheck(False)
@cython.wraparound(False)
def py_hyp1f2( \
        double a,
        double b,
        double c,
        double x,
        double p):
    """
    Hypergeometric function 1F2

    :param a:
    :param b:
    :param c:
    :param x:
    """
    cdef double err
    res = onef2(a, b, c, x, &err)
    if err > p:  # choose a threshold for error
        raise ValueError(f"Computation did not converge, error = {err}")
    return res, err


@cython.boundscheck(False)
@cython.wraparound(False)
def py_hyp3f0( \
        double a,
        double b,
        double c,
        double x,
        double p):
    """
    Hypergeometric function 1F2

    :param a:
    :param b:
    :param c:
    :param x:
    """
    cdef double err
    res = threef0(a, b, c, x, &err)
    if err > p:  # choose a threshold for error
        raise ValueError(f"Computation did not converge, error = {err}")
    return res, err

