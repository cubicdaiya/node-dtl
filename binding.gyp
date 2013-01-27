{
  'targets': [
    {
      'target_name': 'dtl',
      'sources': [
        'src/dtl.cc',
        'src/Dtl.cc',
        'src/Dtl3.cc',
      ],
      'include_dirs' : ['deps/dtl/dtl'],
      'cflags_cc+': ['-O2', '-g', '-Wall'],
    },
  ],
}
