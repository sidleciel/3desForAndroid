package com.rhodes.a3des;

/**
 * Created by xiet on 2016/2/29.
 */
public class Des3 {
    static {
        System.loadLibrary("des3");
    }

    public static native byte[] decrypt(byte[] cipher);
    public static native byte[] encrypt(byte[] plain);
  
}
