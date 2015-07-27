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
	echo "./make.sh [option]" # to be added

	exit 1
}

function build() {
	echo ">>> build $1"
	base_dir=$(pwd)
	case $1 in 
		"n5")
			lunch aosp_hammerhead-eng
			;;
		"n4")
			lunch full_mako-eng
			;;
		"n7")
			lunch aosp_flo-eng
			;;
		"x86")
			lunch android_x86-eng
			;;
		*)
			echo "**** Wrong Target!!! ($1)*****"
			exit 1
			;;
	esac
	rm out/target/product/hammerhead/system/lib/libjni_stencil.so 
	rm out/target/product/hammerhead/system/priv-app/Stencil/lib/arm/libjni_stencil.so 
	rm out/target/product/hammerhead/symbols/system/lib/libjni_stencil.so 
 	rm out/target/product/hammerhead/obj/lib/libjni_stencil.so 
	rm -rf out/target/product/hammerhead/obj/SHARED_LIBRARIES/libjni_stencil_intermediates/
	
	rm -rf out/target/common/obj/APPS/Stencil_intermediates/
	rm -rf out/target/common/R/com/android/korvo/
	
	make -j14

}

function flash() {
	echo ">>> flash $1"
	base_dir=$(pwd)
	case $1 in 
		"n5")
			TARGET="hammerhead"
			;;
		"n4")
			TARGET="mako"
			;;
		"n7")
			TARGET="flo"
			;;
		"x86")
			make -j20 iso_img
			exit 1
			;;
		*)
			echo "**** Wrong Target!!! ($1)*****"
			exit 1
			;;
	esac

	adb reboot fastboot
	echo -e "\t Click power and volume down!!" 
	sleep 10
	fastboot devices
	# fastboot flashall -w
	# fastboot flash recovery out/target/product/$TARGET/recovery.img
	# fastboot flash boot out/target/product/$TARGET/boot.img
	# fastboot flash cache out/target/product/$TARGET/cache.img
	fastboot flash system out/target/product/$TARGET/system.img
	fastboot reboot
	echo -e "\t Flashing done!!"
}

function kernel() {
	echo ">>> kernel build $1"
	base_dir=$(pwd)
	# echo $base_dir
	case $1 in
		"n5")
			kernel_dir="kernel/lge/hammerhead/"
			if [ ! -d "$kernel_dir" ]; then
				echo "**** kernel folder does NOT exist! ****"
				exit 1
			fi
			cd $kernel_dir
			make hammerhead_defconfig -j2
			make -j10
			cp $base_dir/$kernel_dir/arch/arm/boot/zImage* $base_dir/device/lge/hammerhead-kernel/
			cd $base_dir
			;;
		"n4")
			kernel_dir="kernel/lge/mako/"
			if [ ! -d "$kernel_dir" ]; then
				echo "**** kernel folder does NOT exist! ****"
				exit 1
			fi
			cd $kernel_dir
			make mako_defconfig -j2
			make -j10
			cp $base_dir/$kernel_dir/arch/arm/boot/zImage* $base_dir/device/lge/mako-kernel/
			#cp $base_dir/device/lge/mako-kernel/zImage $base_dir/device/lge/mako-kernel/kernel
			cd $base_dir
			;;
		*) 
			echo "Unsupported device $1"
			;;
	esac
}

function init() {
	if [ -z $1 ]
	then
		usage
	elif [ -n $1 ]
	then
	  	arg=$1
	fi

	# include all build script
	. build/envsetup.sh 

	case $arg in
		"kernel") 
			echo "Build kernel"
			kernel $2
			;;
		"flash") 
			echo "Flash device"
			flash $2
			;;
		*)
			echo "build!"
			build $1
			;;
	esac
}

init $1 $2 $3
