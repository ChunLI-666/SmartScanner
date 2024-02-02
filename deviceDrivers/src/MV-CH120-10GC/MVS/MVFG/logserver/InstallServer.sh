#!/bin/bash
DIRNAME=`dirname $0`
PWD=`pwd`
LOGSERVER_PATH=$(cd `dirname $0`; pwd)
SDK_HOME=$(cd ${LOGSERVER_PATH}/../; pwd)
USER_ID=`id -u`
SDK_PATH_OLD=$(cat ${LOGSERVER_PATH}/Debian/MvFGLogServerd | grep "^SDK_HOME=" | awk -F '=' '{print $2}')
FIND_PATH=${SDK_PATH_OLD//\//\\\/}
FIND_PATH=${FIND_PATH//\#/\\\#}
REPLACE_PATH=${SDK_HOME//\//\\\/}
# Check required priviledge
if [ "$USER_ID" != "0" ]; then
echo "LogServer can only be installed by root user or sudoer"
exit 1
fi
  
ARCH=$(uname -m | sed 's/x86_//;s/i[3-6]86/32/')

if [ -f /etc/debian_version ]; then
    OS=Debian  # XXX or Ubuntu??
    VER=$(cat /etc/debian_version)
else
    OS=$(uname -s)
    VER=$(uname -r)
fi

if [ "Debian" = "$OS" ]; then
	sed -i "/^SDK_HOME=*/s/${FIND_PATH}/${REPLACE_PATH}/" ${LOGSERVER_PATH}/Debian/MvFGLogServerd
	cp -f ${LOGSERVER_PATH}/Debian/MvFGLogServerd /etc/init.d/
else
	sed -i "/^SDK_HOME=*/s/${FIND_PATH}/${REPLACE_PATH}/" ${LOGSERVER_PATH}/Debian/MvFGLogServerd
	cp -f ${LOGSERVER_PATH}/Debian/MvFGLogServerd /etc/init.d/
fi

mv -f /etc/init.d/MvFGLogServerd /etc/init.d/MvFGLogServer
chmod 777 /etc/init.d/MvFGLogServer


if [ "Debian" = "$OS" ]; then
	update-rc.d -f MvFGLogServer defaults 1> /dev/null
else
	echo "Can not recognize system"
fi

service MvFGLogServer start

if [ -f "./LogServer.ini" ]; then
	mv LogServer.ini /var/tmp/log/MVFG
fi
