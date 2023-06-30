import numpy as np
from .cython_special import py_hyp1f2, py_hyp3f0

vect_hyp1f2 = np.vectorize(py_hyp1f2)
def hyp1f2(a, b, c, x, precision=1e-9):
    """Vectorized version of py_hyp1f2"""
    x = np.asarray(x)  # Convert input to ndarray if it isn't already
    if np.isscalar(x):
        result, err = py_hyp1f2(a, b, c, x, precision).item()
        return result.item(), err.item()
    else:
        original_shape = x.shape
        result, err = vect_hyp1f2(a, b, c, x.ravel(), precision)
        if result.size == 1:
            return result.item(), err.item()  # convert to scalar
        else:
            return result.reshape(original_shape), err.reshape(original_shape)

vect_hyp3f0 = np.vectorize(py_hyp3f0)
def hyp3f0(a, b, c, x, precision=1e-9):
    """Vectorized version of py_hyp1f2"""
    x = np.asarray(x)  # Convert input to ndarray if it isn't already
    if np.isscalar(x):
        result, err = py_hyp1f2(a, b, c, x, precision).item()
        return result.item(), err.item()
    else:
        result = vect_hyp3f0(a, b, c, x.ravel(), precision)
        if result.size == 1:
            return result.item(), err.item()  # convert to scalar
        else:
            return result.reshape(original_shape), err.reshape(original_shape)
