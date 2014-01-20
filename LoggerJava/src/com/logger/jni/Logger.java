package com.logger.jni;

public class Logger {

	public native void AddThread(String name);
	public native void Init(String path,String name);
	public native void Init(String path,String name,int maxBuf);
	public native void Run();
	private native void Debug(String className,String funName,int lineNum,String message);
	private native void Info(String className,String funName,int lineNum,String message);
	private native void Warn(String className,String funName,int lineNum,String message);
	private native void Error(String className,String funName,int lineNum,String message);
	public native void Finish();
	
	private static Logger logger = null;
	private Logger(){
		System.loadLibrary("LoggerJNI");
	}
	
	public static Logger GetLogger(){
		if(logger == null){
			syncInit();
		}
		
		return logger;
	}
	
	private static synchronized void syncInit() {
		if (logger == null) {
			logger = new Logger();
		}
	}
	
	public void Init(String path){
		String projectname = System.getProperty("user.dir");  
		String pn = projectname.substring(projectname.lastIndexOf('\\')+1,projectname.length());
		Init(path,pn);
	}
	
	public void Init(String path,int maxBuf){
		String projectname = System.getProperty("user.dir");  
		String pn = projectname.substring(projectname.lastIndexOf('\\')+1,projectname.length());
		Init(path,pn,maxBuf);
	}
	
	public void Debug(String message){
		Debug(GetClassName(),GetMethodName(),GetLineNumber(),message);
	}
	
	public void Info(String message){
		Info(GetClassName(),GetMethodName(),GetLineNumber(),message);
	}
	
	public void Warn(String message){
		Warn(GetClassName(),GetMethodName(),GetLineNumber(),message);
	}
	
	public void Error(String message){
		Error(GetClassName(),GetMethodName(),GetLineNumber(),message);
	}
	
	private String GetClassName(){
		return Thread.currentThread().getStackTrace()[3].getClassName();
	}
	
	private String GetMethodName(){
		return Thread.currentThread().getStackTrace()[3].getMethodName();
	}
	
	private int GetLineNumber(){
		return Thread.currentThread().getStackTrace()[3].getLineNumber();
	}
}
