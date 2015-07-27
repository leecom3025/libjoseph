# !bin/bash
#------------------------------------------------------------------------------
# Copyright (C) 2015 HyunJong Joseph Lee, Korvo, Georgia Tech
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#------------------------------------------------------------------------------

function usage() {
	echo "./fetch.sh [option]"
	echo "	zmq - ZeroMQ"
	echo " 	cjson - libcJSON"
	exit 1
}

function init() {
	if [ -z $1 ]
	then
		usage
	elif [ -n $1 ]
	then
	  	arg=$1
	fi

	case $arg in
		"zmq") 
			echo "Fetching zmq~!"
			git clone http://github.com/forkjoseph/android_external_zmq ../../zmq
			;;
		"cjson") 
			echo "Fetching cjson~!"
			git clone http://github.com/forkjoseph/android_external_libcjson ../../libcjson
			;;
		*) 
			echo "WHAT??? $1"
			;;
	esac
}

init $1