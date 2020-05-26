#! /bin/sh

set -ex

./scripts/compile.sh
cd .build && eval ./AsioSyncServer
