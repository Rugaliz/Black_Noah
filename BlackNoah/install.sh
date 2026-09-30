#!/usr/bin/env bash
# Run from the BlackNoah source folder after building (./compile.sh) with sufficient privileges.
set -e

install -Dm644 images/blacknoah.svg /usr/share/icons/hicolor/scalable/apps/blacknoah.svg
install -Dm644 blacknoah.desktop /usr/share/applications/blacknoah.desktop
[ -f build/blacknoah ] && install -Dm755 build/blacknoah /usr/local/bin/blacknoah
exit 0
