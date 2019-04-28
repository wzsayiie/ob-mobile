#!/bin/bash

set -e -u

cd `dirname $0`

cur_path=`pwd`

cmd_line="unity"
cmd_line="$cmd_line -quit"
cmd_line="$cmd_line -batchmode"
cmd_line="$cmd_line -projectPath $cur_path/app_unity"
cmd_line="$cmd_line -executeMethod IOSBuilder.Build"
cmd_line="$cmd_line -logFile"

$cmd_line
