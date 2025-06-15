project(
  'jdfs', 'c',
  license: 'GPL-3.0-or-later',
  version: '0.1.1'
)

# Try to get version string from git or use project version if that fails.
git_describe = run_command('git', 'describe', '--tags', '--always', check: false)
git_describe_out = git_describe.stdout().strip()

tag = 'v' + meson.project_version()

if git_describe_out != ''
  tag = git_describe_out
endif

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
