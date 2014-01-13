using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Diagnostics;

namespace LoggerCsharp
{
    public class Logger
    {
        [DllImport("LoggerCore.dll", EntryPoint = "AddThreadCore", CharSet = CharSet.Auto)]
        public static extern void AddThreadCore(byte[] name);
        [DllImport("LoggerCore.dll", EntryPoint = "InitCore1", CharSet = CharSet.Auto,CallingConvention = CallingConvention.StdCall)]
        public static extern void InitCore1(byte[] path, byte[] name);
        [DllImport("LoggerCore.dll", EntryPoint = "InitCore2", CharSet = CharSet.Auto)]
        public static extern void InitCore2(byte[] path, byte[] name, int maxBuf);
        [DllImport("LoggerCore.dll", EntryPoint = "RunCore", CharSet = CharSet.Auto)]
        public static extern void RunCore();
        [DllImport("LoggerCore.dll", EntryPoint = "DebugCore", CharSet = CharSet.Auto)]
        public static extern void DebugCore(byte[] className, byte[] funName,int lineNum, byte[] message);
        [DllImport("LoggerCore.dll", EntryPoint = "InfoCore", CharSet = CharSet.Auto)]
        public static extern void InfoCore(byte[] className, byte[] funName, int lineNum, byte[] message);
        [DllImport("LoggerCore.dll", EntryPoint = "WarnCore", CharSet = CharSet.Auto)]
        public static extern void WarnCore(byte[] className, byte[] funName, int lineNum, byte[] message);
        [DllImport("LoggerCore.dll", EntryPoint = "ErrorCore", CharSet = CharSet.Auto)]
        public static extern void ErrorCore(byte[] className, byte[] funName, int lineNum, byte[] message);
        [DllImport("LoggerCore.dll", EntryPoint = "FinishCore", CharSet = CharSet.Auto)]
        public static extern void FinishCore();

        private static Logger logger = null;
        private static object padlock = new object();
        private Logger()
        {

        }

        public static Logger GetLogger()
        {
            if (logger == null)
            {
                lock (padlock)
                {
                    if (logger==null)
                    {
                        logger = new Logger();
                    }
                }
            }
            return logger;
        }
        
        public void AddThread(string name)
        {
            AddThreadCore(GetCharArray(name));
        }
        
        public void Init(string filepath)
        {
            Init(filepath, "");
        }
        public void Init(string filepath, string name)
        {
            InitCore1(GetCharArray(filepath), GetCharArray(name));
        }
        public void Init(string filepath, int maxBuffer)
        {
            Init(filepath, "", maxBuffer);
        }
        public void Init(string filepath, string name, int maxBuffer)
        {
            InitCore2(GetCharArray(filepath), GetCharArray(name), maxBuffer);
        }

        public void Run()
        {
            RunCore();
        }

        public void Debug(string message)
        {
            string className = GetClassName();
            string funName = GetMethodName();
            DebugCore(GetCharArray(className),GetCharArray(funName),GetLineName(),GetCharArray(message));
        }

        public void Info(string message)
        {
            string className = GetClassName();
            string funName = GetMethodName();
            InfoCore(GetCharArray(className), GetCharArray(funName), GetLineName(), GetCharArray(message));
        }

        public void Warn(string message)
        {
            string className = GetClassName();
            string funName = GetMethodName();
            WarnCore(GetCharArray(className), GetCharArray(funName), GetLineName(), GetCharArray(message));
        }

        public void Error(string message)
        {
            string className = GetClassName();
            string funName = GetMethodName();
            ErrorCore(GetCharArray(className), GetCharArray(funName), GetLineName(), GetCharArray(message));
        }

        public void Finish()
        {
            FinishCore();
        }
        private byte[] GetCharArray(string str)
        {
            byte[] array = new byte[str.Length + 1];

            for (int i = 0; i < str.Length; i++)
            {
                array[i] = (byte)str[i];
            }

            array[str.Length] = 0;

            return array;
        }

        private string GetClassName()
        {
            MethodBase mb = GetMethodBase();
            return mb.DeclaringType.FullName;
        }

        private string GetMethodName()
        {
            MethodBase mb = GetMethodBase();
            return mb.Name;
        }
        
        private int GetLineName()
        {
            StackTrace ss = new StackTrace(true);
            return ss.GetFrame(2).GetFileLineNumber();
        }
        
        private MethodBase GetMethodBase()
        {
            StackTrace ss = new StackTrace(true);
            MethodBase mb = ss.GetFrame(3).GetMethod();
            return mb;
        }

       
    }
}
