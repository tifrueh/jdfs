# Configure documentation files.

jdfs_date = run_command('git', 'rev-list', '--no-commit-header', '-1', '--format=format:%as', 'HEAD', '--', 'jdfs.1.in', check: true).stdout().strip()
jdfs_data = configuration_data()
jdfs_data.merge_from(conf_data)
jdfs_data.set('date', jdfs_date)
configure_file(
  input: 'jdfs.1.in',
  output: 'jdfs.1',
  configuration: jdfs_data,
  install: true,
  install_dir: get_option('mandir') + '/man1/'
)

jdfs_config_date = run_command('git', 'rev-list', '--no-commit-header', '-1', '--format=format:%as', 'HEAD', '--', 'jdfs-config.1.in', check: true).stdout().strip()
jdfs_config_data = configuration_data()
jdfs_config_data.merge_from(conf_data)
jdfs_config_data.set('date', jdfs_config_date)
configure_file(
  input: 'jdfs-config.1.in',
  output: 'jdfs-config.1',
  configuration: jdfs_config_data,
  install: true,
  install_dir: get_option('mandir') + '/man1/'
)

jdfs_ls_date = run_command('git', 'rev-list', '--no-commit-header', '-1', '--format=format:%as', 'HEAD', '--', 'jdfs-ls.1.in', check: true).stdout().strip()
jdfs_ls_data = configuration_data()
jdfs_ls_data.merge_from(conf_data)
jdfs_ls_data.set('date', jdfs_ls_date)
configure_file(
  input: 'jdfs-ls.1.in',
  output: 'jdfs-ls.1',
  configuration: jdfs_ls_data,
  install: true,
  install_dir: get_option('mandir') + '/man1/'
)

jdfs_path_date = run_command('git', 'rev-list', '--no-commit-header', '-1', '--format=format:%as', 'HEAD', '--', 'jdfs-path.1.in', check: true).stdout().strip()
jdfs_path_data = configuration_data()
jdfs_path_data.merge_from(conf_data)
jdfs_path_data.set('date', jdfs_path_date)
configure_file(
  input: 'jdfs-path.1.in',
  output: 'jdfs-path.1',
  configuration: jdfs_path_data,
  install: true,
  install_dir: get_option('mandir') + '/man1/'
)

jdfs_conf_date = run_command('git', 'rev-list', '--no-commit-header', '-1', '--format=format:%as', 'HEAD', '--', 'jdfs-conf.1.in', check: true).stdout().strip()
jdfs_conf_data = configuration_data()
jdfs_conf_data.merge_from(conf_data)
jdfs_conf_data.set('date', jdfs_conf_date)
configure_file(
  input: 'jdfs.conf.5.in',
  output: 'jdfs.conf.5',
  configuration: jdfs_conf_data,
  install: true,
  install_dir: get_option('mandir') + '/man5/'
)
