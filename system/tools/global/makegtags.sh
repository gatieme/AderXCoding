#!/bin/bash

PROJECT="linux"
LAST_COMMIT=`git rev-parse HEAD`
if [[ $? -ne 0 ]];then
	exit -1
fi

VERSION=`git describe`
if [[ $? -ne 0 ]];then
	echo "something error when git describe"
	VERSION=$PROJECT-${LAST_COMMIT:0:13}
elif [ -z $VERSION ]; then
	echo "no version"
	echo -1
fi

OLDVERSION=`cat .version`

if [ $VERSION != $OLDVERSION ]; then
	gtags –v
	if [[ $? -ne 0 ]];then
		echo "create gtags failed"
		exit -1
	fi

	htags -DfFnva -m start_kernel -t '$VERSION'
	if [[ $? -ne 0 ]];then
		echo "create HTML failed"
		exit -1
	fi

	echo $VERSION > .version
	echo "Create GNU GLOBAL success"
fi
