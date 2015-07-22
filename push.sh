if [[ "init" = $1 ]];
then
	adb shell mount -o rw,remount /
	adb push test.sh /
	adb shell chmod 777 /test.sh
	adb shell mount -o rw,remount /system
	adb push joseph sdcard/
	adb shell ./test.sh
	adb shell chmod 777 /system/bin/joseph
fi
adb push ../../out/target/product/hammerhead/system/bin/joseph sdcard/
adb shell ./test.sh
