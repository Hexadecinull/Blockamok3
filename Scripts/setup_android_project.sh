#!/usr/bin/env bash
# Scaffolds the android/ Gradle project and jni glue if they are not already
# present in the repo.  Called by ci_android.yml.
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
ANDROID="$ROOT/android"
APP="$ANDROID/app/src/main"

echo "==> setup_android_project.sh: scaffolding under $ANDROID"
mkdir -p "$APP/jni" "$APP/c/audio" "$APP/c/fonts" "$APP/res/values"

# ── app/build.gradle ────────────────────────────────────────────────────────
if [ ! -f "$ANDROID/app/build.gradle" ]; then
  cat > "$ANDROID/app/build.gradle" << 'GRADLE'
apply plugin: 'com.android.application'
android {
    namespace 'com.mode8fx.blockamokremix'
    compileSdk 36
    defaultConfig {
        applicationId "com.mode8fx.blockamokremix"
        minSdk 19
        targetSdk 36
        versionCode 1
        versionName "1.0"
        ndk {
            abiFilters 'armeabi-v7a', 'arm64-v8a', 'x86', 'x86_64'
        }
        externalNativeBuild {
            ndkBuild {
                arguments "APP_PLATFORM=android-19",
                          "NDK_MODULE_PATH=src/main/jni"
            }
        }
    }
    externalNativeBuild {
        ndkBuild { path "src/main/jni/Android.mk" }
    }
    buildTypes {
        release { minifyEnabled false }
    }
    compileOptions {
        sourceCompatibility JavaVersion.VERSION_11
        targetCompatibility JavaVersion.VERSION_11
    }
}
dependencies {
    implementation 'androidx.appcompat:appcompat:1.6.1'
}
GRADLE
  echo "  created app/build.gradle"
fi

# ── build.gradle (root) ─────────────────────────────────────────────────────
if [ ! -f "$ANDROID/build.gradle" ]; then
  cat > "$ANDROID/build.gradle" << 'GRADLE'
buildscript {
    repositories { google(); mavenCentral() }
    dependencies { classpath 'com.android.tools.build:gradle:8.3.2' }
}
allprojects { repositories { google(); mavenCentral() } }
GRADLE
  echo "  created build.gradle"
fi

# ── settings.gradle ─────────────────────────────────────────────────────────
if [ ! -f "$ANDROID/settings.gradle" ]; then
  printf 'rootProject.name = "BlockamokRemix"\ninclude ":app"\n' > "$ANDROID/settings.gradle"
  echo "  created settings.gradle"
fi

# ── gradle.properties ───────────────────────────────────────────────────────
if [ ! -f "$ANDROID/gradle.properties" ]; then
  cat > "$ANDROID/gradle.properties" << 'PROPS'
android.useAndroidX=true
android.enableJetifier=true
org.gradle.jvmargs=-Xmx2048m
android.suppressUnsupportedCompileSdk=36
PROPS
  echo "  created gradle.properties"
fi

# ── AndroidManifest.xml ─────────────────────────────────────────────────────
if [ ! -f "$APP/AndroidManifest.xml" ]; then
  cat > "$APP/AndroidManifest.xml" << 'XML'
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android">
  <uses-feature android:glEsVersion="0x00020000" android:required="true" />
  <uses-permission android:name="android.permission.VIBRATE" />
  <application
      android:allowBackup="false"
      android:label="@string/app_name"
      android:hardwareAccelerated="true">
    <activity
        android:name="org.libsdl.app.SDLActivity"
        android:label="@string/app_name"
        android:exported="true"
        android:screenOrientation="landscape"
        android:configChanges="keyboard|keyboardHidden|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode"
        android:launchMode="singleTop">
      <intent-filter>
        <action android:name="android.intent.action.MAIN" />
        <category android:name="android.intent.category.LAUNCHER" />
        <category android:name="android.intent.category.LEANBACK_LAUNCHER" />
      </intent-filter>
      <meta-data android:name="android.app.lib_name" android:value="main" />
    </activity>
  </application>
</manifest>
XML
  echo "  created AndroidManifest.xml"
fi

# ── jni/Android.mk ──────────────────────────────────────────────────────────
if [ ! -f "$APP/jni/Android.mk" ]; then
  cat > "$APP/jni/Android.mk" << 'MK'
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := main
LOCAL_SRC_FILES := \
  $(wildcard $(LOCAL_PATH)/../c/*.c) \
  $(wildcard $(LOCAL_PATH)/../c/audio/*.c) \
  $(wildcard $(LOCAL_PATH)/../c/fonts/*.c)
LOCAL_CFLAGS    += -DANDROID -DNO_QUIT -DFORCE_DRAW_BG -DFORCE_DRAW_OVERLAY -O2
LOCAL_LDLIBS    := -lGLESv1_CM -lGLESv2 -llog
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_ttf
include $(BUILD_SHARED_LIBRARY)
$(call import-module,SDL2)
$(call import-module,SDL2_mixer)
$(call import-module,SDL2_ttf)
MK
  echo "  created jni/Android.mk"
fi

# ── jni/Application.mk ──────────────────────────────────────────────────────
if [ ! -f "$APP/jni/Application.mk" ]; then
  printf 'APP_ABI    := armeabi-v7a arm64-v8a x86 x86_64\nAPP_PLATFORM := android-19\nAPP_ALLOW_MISSING_DEPS := true\n' \
    > "$APP/jni/Application.mk"
  echo "  created jni/Application.mk"
fi

# ── res/values/strings.xml ──────────────────────────────────────────────────
if [ ! -f "$APP/res/values/strings.xml" ]; then
  cat > "$APP/res/values/strings.xml" << 'XML'
<?xml version="1.0" encoding="utf-8"?>
<resources>
    <string name="app_name">Blockamok Remix</string>
</resources>
XML
  echo "  created res/values/strings.xml"
fi

echo "==> setup_android_project.sh: done"
