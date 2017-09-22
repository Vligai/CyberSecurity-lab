To create Hello World app I used Android Studio blank project, which generated a Hello World app.

To edit my hello world app I decompiled it, edited values and recompiled it. After recompiling it I generated a key and signed it with that key. To install this apk on emulated device go to SDK directory and follow steps below.

To edit notepad app I followed the same procedure as when editing my Hello World app. The only thing that was different is that I changed the permissions required by the application.

Permissions added:
    <uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.SEND_SMS" />
    <uses-permission android:name="android.permission.READ_CALL_LOG" />
    <uses-permission android:name="android.permission.READ_CONTACTS" />
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.READ_LOGS" />
    <uses-permission android:name="android.permission.REBOOT" />
    <uses-permission android:name="android.permission.READ_VOICEMAIL" />

Decompile: java -jar apktool.jar d -s[name of the app]

Recompile: java -jar apktool.jar b [name of the app]

Generating a key: keytool -genkey -v -keystore my-release-key.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000

Signing the apk: jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore my-release-key.keystore my_application.apk alias_name

installing the signed app on emulator:
"C:\Users\Class2017\AppData\Local\Android\sdk\platform-tools" 
~ adb devices
~ adb install "C:\Users\Class2017\Desktop\lab7\app-release-signed.apk"

Nexus 5 API 23 -> Signed APK hello world app, signed notepad app

Nexus 5 API 23 x86 -> Hello World app, notepad app

Sources:
http://forum.xda-developers.com/showthread.php?t=2213985
http://developer.android.com/tools/publishing/app-signing.html
http://androidthon.info/how-to-install-apk-file-on-android-emulator/