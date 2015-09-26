package joseph.torh;

/* 
 *	Usage:
 *		double temp = Torh.getTemp();
 * 		double util = Torh.getUtil();
 * 		double freq = Torh.getFreq();
 */
public class Torh {
//	public native static void check();
	public native static void init();
	public native static double getTemp();
	public native static double getUtil();
	public native static double getFreq();

	static {
		System.loadLibrary("joseph_jni");
		init();
	}

}
