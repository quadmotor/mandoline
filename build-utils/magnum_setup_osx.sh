#!/bin/bash
# http://stackoverflow.com/questions/3572030/bash-script-absolute-path-with-os-x
realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

TMPDIR="$1"
IMGUI_DIR=$( realpath "$2" )
SCRIPT_DIR=$( realpath "$3" )
echo "SCRIPT DIR: ${SCRIPT_DIR}"
echo "TMPDIR DIR: ${SCRIPT_DIR}"
pushd "$TMPDIR/mosra"
pushd magnum-integration;

sed "s|IMDIR|${IMGUI_DIR}|g" ${SCRIPT_DIR}/magnum_integration_homebrew.patch > magnum_integration_imgui.patch
patch -b ./package/homebrew/magnum-integration magnum_integration_imgui.patch
popd #magnum integration

for repo in corrade magnum magnum-integration;
do pushd $repo;
    brew install package/homebrew/${repo}.rb
    popd
done
popd
