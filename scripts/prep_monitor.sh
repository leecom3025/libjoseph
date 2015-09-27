
adb wait-for-device root 
adb shell stop mdprecision
adb shell "echo ondemand > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
adb shell "echo ondemand > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor"
adb shell "echo ondemand > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor"
adb shell "echo ondemand > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor"
