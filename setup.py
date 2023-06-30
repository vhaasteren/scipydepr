from setuptools import setup, find_packages
from setuptools import Extension
from Cython.Build import cythonize


__version__ = "0.0.1"

ext_modules=[
    Extension(
        name='scipydepr.special.cython_special',
        sources=[
                'scipydepr/special/cython_special.pyx',
            ],
        extra_compile_args=["-O2", "-fno-wrapv"])
]


setup(
    name="scipydepr",
    version=__version__,
    description="Deprecated functions from Scipy (scipy.special) for those of us who need them",
    license='BSD',
    author="Rutger van Haasteren",
    author_email="rutger@vhaasteren.com",
    packages=find_packages(),
    url="http://github.com/vhaasteren/scipydepr/",
    long_description=open("README.md").read(),
    include_package_data=True,
    zip_safe=False,
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: BSD",
        "Operating System :: OS Independent",
        "Programming Language :: Python",
    ],
    ext_modules = cythonize(ext_modules),
    package_data={
        "scipydepr": ["README", "LICENSE", "AUTHORS.md"],
        "scipydepr.special": [
                    "special/cython_special.pyx",
                    "special/special.py",
            ],
    },
)
