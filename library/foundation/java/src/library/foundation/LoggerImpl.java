package src.library.foundation;

import android.util.Log;

class LoggerImpl extends Logger {

    public static void info(String message) {
        Log.i("zzz", message);
    }

    public static void error(String message) {
        Log.e("zzz", message);
    }
}