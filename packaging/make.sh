#!/usr/bin/env bash
#
# Host entrypoint: builds the ros:noetic packaging image and runs it to produce
# ros-noetic-pairs-msgs_*.deb and ros-noetic-pairs-lib_*.deb.
#
# Run from anywhere; paths are resolved relative to this script.
# Output .deb files land in   <repo>/packaging/output/
#
# Requirements on the host: docker. (Works on any Ubuntu, incl. 24.04.)
#
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(dirname "$SCRIPT_DIR")"          # .../src/pairs_lib
SRC_DIR="$(dirname "$REPO_DIR")"             # .../src  (contains pairs_lib + pairs_msgs)
OUTPUT_DIR="$SCRIPT_DIR/output"
IMAGE="pairs-lib-noetic-packaging"

mkdir -p "$OUTPUT_DIR"

echo ">> Building packaging image ($IMAGE)..."
docker build -t "$IMAGE" "$SCRIPT_DIR"

echo ">> Building .deb packages (output -> $OUTPUT_DIR)..."
docker run --rm \
  -v "$SRC_DIR":/src:ro \
  -v "$OUTPUT_DIR":/output \
  "$IMAGE"

echo ">> Done. Artifacts:"
ls -1 "$OUTPUT_DIR"/*.deb
