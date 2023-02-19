from distutils.core import setup, Extension
setup(name='VectorizeList',
      version='1.1.0',
      ext_modules = [Extension('VectorizeList', sources=['VectorizeList.c'], include_dirs=['.'])],
      license="GNU3",
      description="Vectorize a list of strings into ints",
      author="Julien Calenge",
      author_email="julien.calenge@epitech.eu",
      url="https://github.com/jclge/VectorizeList",
      download_url="https://github.com/jclge/VectorizeList/archive/refs/tags/v1.0.tar.gz"
      )
