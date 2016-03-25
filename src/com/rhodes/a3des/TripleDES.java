package com.rhodes.a3des;

import android.util.Base64;

import java.security.NoSuchAlgorithmException;
import java.security.Security;
import java.util.Random;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESedeKeySpec;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/**
 * Created by caowd on 2016/2/25.
 */
public class TripleDES {

    // 密钥
//    private final static String secretKey = "9UNfI9GE4UTSESF9fXW4et40";
    public final static String secretKey = "Exr8FSx3nW3K5vcOZgw6Mb3o";
    // 向量
    private final static String iv        = "TzeLz8sk";

    static {
        Security.addProvider(new com.sun.crypto.provider.SunJCE());
    }
    
    //----------DESede/CBC 算法----------

    private static final String MCRYPT_TRIPLEDES = "DESede";
    private static final String TRANSFORMATION   = "DESede/CBC/PKCS5Padding";

    public static byte[] decrypt(byte[] data, byte[] key, byte[] iv) throws Exception {
        DESedeKeySpec    spec         = new DESedeKeySpec(key);
        SecretKeyFactory keyFactory   = SecretKeyFactory.getInstance(MCRYPT_TRIPLEDES);
        SecretKey        sec          = keyFactory.generateSecret(spec);
        Cipher           cipher       = Cipher.getInstance(TRANSFORMATION);
        IvParameterSpec  IvParameters = new IvParameterSpec(iv);
        cipher.init(Cipher.DECRYPT_MODE, sec, IvParameters);
        return cipher.doFinal(data);
    }

    public static byte[] encrypt(byte[] data, byte[] key, byte[] iv) throws Exception {
        DESedeKeySpec    spec         = new DESedeKeySpec(key);
        SecretKeyFactory keyFactory   = SecretKeyFactory.getInstance("DESede");
        SecretKey        sec          = keyFactory.generateSecret(spec);
        Cipher           cipher       = Cipher.getInstance(TRANSFORMATION);
        IvParameterSpec  IvParameters = new IvParameterSpec(iv);
        cipher.init(Cipher.ENCRYPT_MODE, sec, IvParameters);
        return cipher.doFinal(data);
    }

    public static byte[] generateSecretKey() throws NoSuchAlgorithmException {
        KeyGenerator keygen = KeyGenerator.getInstance(MCRYPT_TRIPLEDES);
        return keygen.generateKey().getEncoded();
    }

    public static byte[] randomIVBytes() {
        Random ran   = new Random();
        byte[] bytes = new byte[8];
        for (int i = 0; i < bytes.length; ++i) {
            bytes[i] = (byte) ran.nextInt(Byte.MAX_VALUE + 1);
        }
        return bytes;
    }

    //加密方法

    public static String encode(String plainText) {

        try {
            final byte[] secretBytes = secretKey.getBytes();

            final byte[] ivbytes = iv.getBytes();

            byte[] encrypt = TripleDES.encrypt(plainText.getBytes(), secretBytes, ivbytes);

            return new String(Base64.encode(encrypt, Base64.DEFAULT));
        } catch (Exception e) {
            return "";
        }
    }

    public static void main(String args[]) throws Exception {
        String       plainText   = "a12*&1c中文";
        final byte[] secretBytes = secretKey.getBytes();

        final byte[] ivbytes = TripleDES.randomIVBytes();
        System.out.println("plain text: " + plainText);
        byte[] encrypt = TripleDES.encrypt(plainText.getBytes(), secretBytes, ivbytes);
        System.out.println("cipher text: " + encrypt);
        System.out.println("decrypt text: " + new String(TripleDES.decrypt(encrypt, secretBytes, ivbytes), "UTF-8"));

        
        //cbc mode test
        /*System.out.println("plain text(ECB): " + plainText);
        byte[] encrypt1 = TripleDES.encrypt1(plainText.getBytes(), secretBytes);
        System.out.println("cipher text: " + encrypt1);
        System.out.println("decrypt text: " + new String(TripleDES.decrypt1(encrypt, secretBytes), "UTF-8"));*/
    }
    
    
    
    //----------DESede/ECB 算法----------
    

//    private static final String TRANSFORMATION1   = "DESede/ECB/NoPadding";
    private static final String TRANSFORMATION1   = "DESede/ECB/PKCS5Padding";
//    private static final String TRANSFORMATION1   = "DESede/ECB/PKCS7Padding";

    public static byte[] decrypt1(byte[] data, byte[] key) throws Exception {
        DESedeKeySpec    spec         = new DESedeKeySpec(key);
        SecretKeyFactory keyFactory   = SecretKeyFactory.getInstance(MCRYPT_TRIPLEDES);
        SecretKey        sec          = keyFactory.generateSecret(spec);
        Cipher           cipher       = Cipher.getInstance(TRANSFORMATION1);
        cipher.init(Cipher.DECRYPT_MODE, sec);
        return cipher.doFinal(data);
    }

    public static byte[] encrypt1(byte[] data, byte[] key) throws Exception {
        DESedeKeySpec    spec         = new DESedeKeySpec(key);
        SecretKeyFactory keyFactory   = SecretKeyFactory.getInstance(MCRYPT_TRIPLEDES);
        SecretKey        sec          = keyFactory.generateSecret(spec);
        Cipher           cipher       = Cipher.getInstance(TRANSFORMATION1);
        cipher.init(Cipher.ENCRYPT_MODE, sec);
        return cipher.doFinal(data);
    }

    public static byte[] decrypt2(byte[] data, String key) throws Exception {
        return initCipher(key,Cipher.DECRYPT_MODE).doFinal(data);
    }

    public static byte[] encrypt2(byte[] data, String key) throws Exception {
        return initCipher(key,Cipher.ENCRYPT_MODE).doFinal(data);
    }
  
    public static final Cipher initCipher(String key,int mode)  
    {  
        try  
        {  
            // 添加新安全算法:PKCS7  
            Security.addProvider(new com.sun.crypto.provider.SunJCE());  
            String algorithm = TRANSFORMATION1;  
            SecretKey desKey = new SecretKeySpec(key.getBytes("ASCII"), MCRYPT_TRIPLEDES);  
            Cipher tcipher = Cipher.getInstance(algorithm);  
            tcipher.init(mode, desKey);  
            return tcipher;  
        } catch (Exception e)  
        {  
            e.printStackTrace();  
        }  
        return null;  
    } 
  

}
