#!/bin/bash
# OrniFlight site watcher — auto-rebuilds on .haml/.sass/.json/.md changes
cd "$(dirname "$0")"
unset RUBYOPT
export BUNDLE_GEMFILE="$PWD/Gemfile"
exec bundle exec rake watch
