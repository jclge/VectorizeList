from distutils.core import setup, Extension
setup(name = 'VectorizeList', version = '1.0', ext_modules = [Extension('VectorizeList', ['VectorizeList.c'])])
