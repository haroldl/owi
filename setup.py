from distutils.core import setup, Extension

owiedge = Extension('owiedge',
                    sources = ['pyowi.c', 'libowi.c'],
                    libraries = ['usb-1.0'])

setup(name = 'owiedge',
      version = '1.0',
      description = 'Provides control of an OWI Edge robot arm kit via the optional USB connector.',
      author = 'Harold Lee',
      author_email = 'harold@hotelling.net',
      url = 'https://github.com/haroldl/owi',
      ext_modules = [owiedge])

