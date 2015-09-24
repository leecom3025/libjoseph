function init() {
	adb wait-for-device root && sleep 1 && adb wait-for-device remount
	if [[ "init" = $1 ]];
	then
		adb shell mount -o rw,remount /
		adb push test.sh /
		adb shell chmod 777 /test.sh
		adb shell mount -o rw,remount /system
		adb push joseph sdcard/
		adb shell ./test.sh
		adb shell chmod 777 /system/bin/joseph
		adb shell mkdir /data/joseph
		adb shell "echo 123 > data/joseph/int_test"
		adb shell "echo \"This is test message\" > data/joseph/string_test"
		adb shell "echo 123.456 > data/joseph/double_test"
		adb shell "echo 123.45 > data/joseph/float_test"
	fi
}

function push() {
	declare -a arr=($(echo $TARGET_PRODUCT | cut -d '_' --output-delimiter="; " -f1-))
	local product=${arr[1]}
	echo ">>>>> $product"
	#adb push ../../out/target/product/$product/system/bin/joseph system/bin/joseph
	adb push ../../out/target/product/$product/system/bin/torhmonitor system/bin/torhmonitor
#	adb shell scripts/test.sh
}

init $1
push $1
