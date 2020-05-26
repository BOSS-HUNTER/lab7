#! /bin/sh

docker stop lab0307_cont

set -ex
eval docker run --rm                             \
           -it                                   \
	   -v $(pwd):/var/builder/               \
	   -w /var/builder                       \
	   -p 8001:8001                          \
	   --entrypoint ./scripts/compile-run.sh \
	   --name lab0307_cont                   \
	   toliak/bootstrap-cpp
