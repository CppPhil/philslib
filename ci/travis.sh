#!/bin/bash

catch_errors() {
  printf "\ntravis.sh failed!\n" >&2
  exit 1
}

trap catch_errors ERR;

build_types=(
  Debug
  Release
)

architectures=(
  x64
  x68
)

generate() {
  build_type="$1"
  arch="$2"
  CXX=/usr/bin/$(printenv COMPILER) cmake -DCMAKE_BUILD_TYPE="$build_type" -DARCH="$arch" -DPL_BUILD_TESTS=ON ..
}

build() {
  cmake --build . -- -j$(nproc)
}

run_tests() {
  ctest --verbose .
}

main() {
  for build_type in "${build_types[@]}"; do
    for arch in "${architectures[@]}"; do
      echo "$build_type $arch"
      mkdir "${build_type}_$arch"
      cd "${build_type}_$arch"
      generate "$build_type" "$arch"
      build
      run_tests
      cd ..
    done
  done  
}

main
exit 0

