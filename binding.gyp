{
  'targets': [
    {
      'target_name': 'dtl',
      'sources': [
        'src/dtl.cc',
        'src/Diff.cc',
        'src/Diff3.cc',
      ],
      'include_dirs' : ['deps/dtl/dtl'],
      'cflags_cc+': ['-O2', '-g', '-Wall'],
    },
  ],
}
