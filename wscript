import Options
import os

srcdir  = '.'
blddir  = 'build'
dtldir  = os.path.abspath(srcdir) + "/deps/dtl"
VERSION = '0.0.5'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target   = 'dtl'
  obj.source   = bld.glob('src/*.cc')
  obj.includes = [dtldir + '/dtl']
  obj.cxxflags = ['-O2', '-g', '-Wall']
 
def shutdown():
  if Options.commands['clean']:
    if os.path.lexists('dtl.node'): 
      os.unlink('dtl.node')
  else:
    if os.path.exists('build/default/dtl.node') and not os.path.lexists('dtl.node'):
      os.symlink('build/default/dtl.node', 'dtl.node')
