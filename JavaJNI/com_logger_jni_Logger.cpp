#include "LoggerCore.h"
#include "com_logger_jni_Logger.h"

#pragma comment(lib,"LoggerCore")

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_AddThread
	(JNIEnv *env, jobject obj, jstring name)
{
	const char* str = env->GetStringUTFChars(name, 0);
	AddThreadCore(str);
	env->ReleaseStringUTFChars(name, 0);
	
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Init__Ljava_lang_String_2Ljava_lang_String_2
	(JNIEnv *env, jobject obj, jstring path, jstring name)
{
	const char* pstr = env->GetStringUTFChars(path, 0);
	const char* nstr = env->GetStringUTFChars(name, 0);
	
	InitCore1(pstr,nstr);
	
	env->ReleaseStringUTFChars(path, 0);
	env->ReleaseStringUTFChars(name, 0);
	
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Init__Ljava_lang_String_2Ljava_lang_String_2I
	(JNIEnv *env, jobject obj, jstring path, jstring name, jint maxBuf)
{
	const char* pstr = env->GetStringUTFChars(path, 0);
	const char* nstr = env->GetStringUTFChars(name, 0);

	InitCore2(pstr,nstr,maxBuf);

	env->ReleaseStringUTFChars(path, 0);
	env->ReleaseStringUTFChars(name, 0);
	

}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Run
	(JNIEnv *env, jobject obj)
{
	RunCore();
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Debug
	(JNIEnv *env, jobject obj, jstring className, jstring funName, jint lineNum, jstring message)
{
	const char* cls = env->GetStringUTFChars(className, 0);
	const char* fun = env->GetStringUTFChars(funName, 0);
	const char* msg = env->GetStringUTFChars(message,0);

	DebugCore(cls,fun,lineNum,msg);
	
	env->ReleaseStringUTFChars(className, 0);
	env->ReleaseStringUTFChars(funName, 0);
	env->ReleaseStringUTFChars(message,0);
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Info
	(JNIEnv *env, jobject obj, jstring className, jstring funName, jint lineNum, jstring message)
{
	const char* cls = env->GetStringUTFChars(className, 0);
	const char* fun = env->GetStringUTFChars(funName, 0);
	const char* msg = env->GetStringUTFChars(message,0);

	InfoCore(cls,fun,lineNum,msg);

	env->ReleaseStringUTFChars(className, 0);
	env->ReleaseStringUTFChars(funName, 0);
	env->ReleaseStringUTFChars(message,0);
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Warn
	(JNIEnv *env, jobject obj, jstring className, jstring funName, jint lineNum, jstring message)
{
	const char* cls = env->GetStringUTFChars(className, 0);
	const char* fun = env->GetStringUTFChars(funName, 0);
	const char* msg = env->GetStringUTFChars(message,0);

	WarnCore(cls,fun,lineNum,msg);

	env->ReleaseStringUTFChars(className, 0);
	env->ReleaseStringUTFChars(funName, 0);
	env->ReleaseStringUTFChars(message,0);
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Error
	(JNIEnv *env, jobject obj, jstring className, jstring funName, jint lineNum, jstring message)
{
	const char* cls = env->GetStringUTFChars(className, 0);
	const char* fun = env->GetStringUTFChars(funName, 0);
	const char* msg = env->GetStringUTFChars(message,0);

	ErrorCore(cls,fun,lineNum,msg);

	env->ReleaseStringUTFChars(className, 0);
	env->ReleaseStringUTFChars(funName, 0);
	env->ReleaseStringUTFChars(message,0);
}

JNIEXPORT void JNICALL Java_com_logger_jni_Logger_Finish
	(JNIEnv *env, jobject obj)
{
	FinishCore();
}