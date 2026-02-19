#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
SNAPSHOT_DIR="$ROOT_DIR/backup/snapshots"
EXPORT_DIR="$ROOT_DIR/backup/dashboard_exports"
TIMESTAMP="$(date +%Y%m%d-%H%M%S)"
ARCHIVE_NAME="thingsboard-project-${TIMESTAMP}.tar.gz"
ARCHIVE_PATH="$SNAPSHOT_DIR/$ARCHIVE_NAME"

mkdir -p "$SNAPSHOT_DIR" "$EXPORT_DIR"

echo "Creating project snapshot..."
tar -czf "$ARCHIVE_PATH" \
  -C "$ROOT_DIR" \
  config \
  notes \
  backup/dashboard_exports

echo "Backup created: $ARCHIVE_PATH"
echo "Archive contents:"
tar -tzf "$ARCHIVE_PATH" | sed -n '1,40p'
