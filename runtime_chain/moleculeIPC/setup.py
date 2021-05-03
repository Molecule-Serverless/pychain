from distutils.core import setup, Extension

setup(name='moleculeIPC',
      ext_modules=[
        Extension('moleculeIPC',
                  ['moleculeIPC.c', 'moleculeIPC_api.c'],
                  include_dirs = ['moleculeOS-userlib/include', 'moleculeOS-userlib/local-ipc'],
                  library_dirs = ['/usr/local/lib', 'moleculeOS-userlib'],
                  libraries = ['moleculeos']
                  )
        ]   
)