package joseph.torh;

public class Torh {
	public native static void check();
	public native static double getTemp();
	public native static double getUtil();
	public native static double getFreq();

	static {
		System.loadLibrary("joseph_jni");
		check();
	}

}
