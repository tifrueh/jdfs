project(
  'jdfs', 'c',
  license: 'GPL-3.0-or-later',
  version: '0.1.1-git'
)

# Get version string from version control.
git_describe = run_command('git', 'describe', '--tags', '--always', '--dirty=*', check: true)
tag = git_describe.stdout().strip()

# Define a variable for configuration data.
conf_data = configuration_data()

# Set up configuration data.
conf_data.set('version', tag.substring(1))
conf_data.set('tag', tag)

# Set up an include list.
incdir = include_directories('include')

# Set up a source list.
src = files()

# Execute the include subdir.
subdir('include')

# Execute the src subdir.
subdir('src')

# Execute the Documentation subdir.
subdir('Documentation')

jdfs = executable(
  'jdfs', src,
  include_directories: incdir,
  install: true,
)
