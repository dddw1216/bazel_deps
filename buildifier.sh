#!/bin/bash
set -xeuo pipefail

buildifier_bin_path="${1}"
search_directory="."
echo "buildifier_bin_path="${buildifier_bin_path}
build_files=$(find "$search_directory" -type f -name 'BUILD')
for build_file in $build_files; do
  echo "buildifier $build_file"
  eval "$buildifier_bin_path \"$build_file\""
done
build_files=$(find "$search_directory" -type f -name '*.BUILD')
for build_file in $build_files; do
  echo "buildifier $build_file"
  eval "$buildifier_bin_path \"$build_file\""
done
