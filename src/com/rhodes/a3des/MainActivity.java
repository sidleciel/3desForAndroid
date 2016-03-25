package com.rhodes.a3des;

import java.util.Arrays;

import android.app.Activity;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	Button exec;
	Button execDe;
	EditText cipherTv;
	EditText secretKeyTv;
	EditText ivParamTv;
	EditText logTv;

	String secretKey = "";
	String plainText = "";
	String iv = "";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		exec = (Button) findViewById(R.id.encryptBtn);
		execDe = (Button) findViewById(R.id.decryptBtn);
		cipherTv = (EditText) findViewById(R.id.cipher);
		secretKeyTv = (EditText) findViewById(R.id.secret_key);
		ivParamTv = (EditText) findViewById(R.id.iv_param);
		logTv = (EditText) findViewById(R.id.log);
		ivParamTv.setVisibility(View.GONE);

		exec.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				plainText = cipherTv.getText().toString();
				soEncrypt(plainText);
			}
		});

		execDe.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				String cipher = logTv.getText().toString();
				soDecrypt(cipher);
			}
		});
		
		doSomething();
	}
	
	private String soEncrypt(String plain) {
		String TAG = "soEncrypt...";
		String secretKey = getResources().getString(R.string.secret_key1);
		
		byte[] encrypt = Des3.encrypt(plain.getBytes());
		Log.i(TAG, "encrypt bytes: " + Arrays.toString(encrypt));
		String encryptBase64 = Base64.encodeToString(encrypt, Base64.DEFAULT);
		Log.i(TAG, "encrypt base64: " + encryptBase64);
		
		logTv.setText(encryptBase64);
		
		return encryptBase64;
	}
	
	private String soDecrypt(String cipher) {
		String TAG = "soDecrypt...";
		String secretKey = getResources().getString(R.string.secret_key1);

		byte[] decrypt = Des3.decrypt(Base64.decode(cipher, Base64.DEFAULT));
		Log.i(TAG, "decrypt bytes: " + Arrays.toString(decrypt));
		String decryptStr = new String(decrypt);
		Log.i(TAG, "decrypt text: " + decryptStr);
		
		cipherTv.setText(decryptStr);
		
		return decryptStr;
	}

	private void doSomething() {

		secretKey = secretKeyTv.getText().toString();
		plainText = cipherTv.getText().toString();

//		System.out.println("---javaEncrypt start---");
//		javaEncrypt();
//		System.out.println("---javaEncrypt end---\n");

		System.out.println("---soEncrypt start---");
		soEncryptTest();
		System.out.println("---soEncrypt end---\n");

	}

	private void soEncryptTest() {
		String TAG = "soEncryptTest";

		String plain = plainText;
		plain = "123456789";
		// plain="abcdef78";
		plain = "a12*&1c中文";
//		String s="{\"account\":\"游客31164\",\"avatarSrc\":\"http://ctimg.mg3721.com/upload/images/headportrait/public/system_14.png\",\"exp\":\"100\",\"gameName\":\"\",\"userName\":\"游客 31164\",\"mobile\":\"\",\"token\":\"rV0852k69nohRJxI\",\"pass\":\"55e2f82b05465492e344e013125a4491\",\"surplusExp\":\"1\",\"registerTime\":1457335977,\"status\":false,\"papaMoney\":100,\"u id\":31164,\"level\":1,\"gender\":0}";
//		String s="{\"account\":\"pa516412\",\"avatarSrc\":\"http://ctimg.mg3721.com/upload/images/headportrait/public/system_12.png\",\"exp\":\"200\",\"gameName\":\"\",\"userName\":\"pa516412\",\"mobile\":\"13061639615\",\"token\":\"2Cf5BQWtcpdEdlOa\",\"pass\":\"123456\",\"surplusExp\":\"101\",\"registerTime\":1457494009,\"status\":false,\"papaMoney\":200,\"uid\":3084812,\"level\":2,\"gender\":1}";
		String s="{\"account\":\"pa51431\",\"avatarSrc\":\"http://ctimg.mg3721.com/upload/images/headportrait/public/system_14.png\",\"exp\":\"200\",\"gameName\":\"\",\"userName\":\"pa51431\",\"mobile\":\"18628913935\",\"token\":\"AamKv0albaeLsFBE\",\"pass\":\"qqqqqq\",\"surplusExp\":\"101\",\"registerTime\":1453971183,\"status\":false,\"papaMoney\":200,\"uid\":2224443,\"level\":2,\"gender\":1}";
//		plain = s;
		
		byte[] encrypt_test = new byte[] { (byte) 0x9e, (byte) 0xdd, 0x31, (byte) 0xe6, (byte) 0xb7, 0x52, (byte) 0xe8,
				(byte) 0x9d, (byte) 0x9e, (byte) 0xdd, 0x31, (byte) 0xe6, (byte) 0xb7, 0x52, (byte) 0xe8, (byte) 0x9d };

		// 1.转为base64，去掉中文和特殊字符
//		plain = Base64.encodeToString(plain.getBytes(), Base64.DEFAULT);
//		plain="eyJhY2NvdW50Ijoi5ri45a6iMzExNjQiLCJhdmF0YXJTcmMiOiJodHRwOi8vY3RpbWcubWczNzIxLmNvbS91cGxvYWQvaW1hZ2VzL2hlYWRwb3J0cmFpdC9wdWJsaWMvc3lzdGVtXzE0LnBuZyIsImV4cCI6IjEwMCIsImdhbWVOYW1lIjoiIiwidXNlck5hbWUiOiLmuLjlrqIzMTE2NCIsIm1vYmlsZSI6IiIsInRva2VuIjoiclYwODUyazY5bm9oUkp4SSIsInBhc3MiOiI1NWUyZjgyYjA1NDY1NDkyZTM0NGUwMTMxMjVhNDQ5MSIsInN1cnBsdXNFeHAiOiIxIiwicmVnaXN0ZXJUaW1lIjoxNDU3MzM1OTc3LCJzdGF0dXMiOmZhbHNlLCJwYXBhTW9uZXkiOjEwMCwidWlkIjozMTE2NCwibGV2ZWwiOjEsImdlbmRlciI6MH0=";
//		String encryptBase64="wC4iTtuzm1btGyL1t4oFmoDpqtpp2kzCJxTS1yvvzw460voN7jVOzOoLbEaaIxUqnvT/Ljbt8c3MmQa0DSZ2sRrpHXVWEI2KzVGYZVefAzijSB3pU5iMGKFJGeAkM3fJQEc9UdBmZcDp/yz9A2MT0l6HwPfe2kP3NLtOmueNbl9xOUwCDF00AM4hZzeky+G3Xa1Uyzu8odL2Jhu4XQK6TCpZ0IjkX0FCJegwy0a9VBJy77jfPvVLENm1EgQNoMtQIRxRCKEiQUWkelR6DDmiE6FDfzSddcAToviiyWsWSFXJfQkESQ+MAHSPchtcFPDmZTZ3a4SmSnnXQOiVo+k6n7nK7n1XqQxO5kpgTD0ThvzJsiFrDWdesYlC+NA3ZwaoUXwxMbRn9GrO+SQZD3zS4r4b3EpFV8JbHNHQMQQAiSeOETSPa9bC2jly5jAj/56TwS+O/dSq/LSkHcWn2T2I8QgSlsKcHPDgJiKWQC6DTaWVZiSOHkzn1YFTiLq55v86KoBueqsGcZEpX08KkTrj42BF7l7CCjjbaYFDvjHu/cvilrCQTamlVwLTMEZl4lIxiZjRCmzJ8CkBVFPMtzG6YJDF5z7uS49o=";
//		Log.i(TAG, "plain text base64: " + plain);
		
		secretKey = "9UNfI9GE4UTSESF9fXW4et40";
		try {
			Log.i(TAG, "encrypt...");
			// 2.key在so中，9UNfI9GE4UTSESF9fXW4et40（24字节）
			byte[] encrypt = Des3.encrypt(plain.getBytes());
			// byte[] encrypt = TripleDES.encrypt1(plain.getBytes(),  secretKey.getBytes());//模拟服务端加密本地解密
			Log.i(TAG, "encrypt bytes: " + Arrays.toString(encrypt));
			String encryptBase64 = Base64.encodeToString(encrypt, Base64.DEFAULT);
			Log.i(TAG, "encrypt base64: " + encryptBase64);

			Log.i(TAG, "decrypt...");
			byte[] decrypt = Des3.decrypt(Base64.decode(encryptBase64, Base64.DEFAULT));
			Log.i(TAG, "decrypt bytes: " + Arrays.toString(decrypt));
			Log.i(TAG, "decrypt text(UTF-8): " + new String(decrypt, "UTF-8"));
//			Log.i(TAG, "decrypt text(BASE64 DECODE): " + new String(Base64.decode(decrypt, Base64.DEFAULT)));
//			Log.i(TAG, "decrypt text(ISO-8859-1): " + new String(decrypt, "ISO-8859-1"));

			Log.i(TAG, "remote decrypt...");
			// 3.so加密采用DESede/ECB/PKCS5Padding。所以java或服务端解密时也采用此模式。
			String jstr = new String(TripleDES.decrypt1(encrypt, secretKey.getBytes()), "UTF-8");
			System.out.println("remote decrypt text: " + jstr);
			// 4.解密明文
//			System.out.println("remote decrypt text origin: " + new String(Base64.decode(jstr, Base64.DEFAULT)));
			System.out.println("remote decrypt bytes: " + Arrays.toString(jstr.getBytes("utf-8")));

		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	private void javaEncrypt() {
		//DESede/ECB/PKCS5Padding

		final byte[] secretBytes = secretKey.getBytes();

		final byte[] ivbytes = TripleDES.randomIVBytes();
		System.out.println("plain text: " + plainText);
		System.out.println("plain bytes: " + Arrays.toString(plainText.getBytes()));
		byte[] encrypt = new byte[0];

		try {
			encrypt = TripleDES.encrypt1(plainText.getBytes(), secretBytes);
			System.out.println("cipher text: " + Arrays.toString(encrypt));
			System.out.println("cipher base64: " + Base64.encodeToString(encrypt, Base64.DEFAULT));
			System.out
					.println("decrypt text: " + new String(TripleDES.decrypt1(encrypt, secretBytes), "UTF-8"));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
