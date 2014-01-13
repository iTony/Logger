using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace Test
{
    class Program
    {
        [DllImport("LoggerCore.dll", EntryPoint = "AddThreadCore", CharSet = CharSet.Auto)]
        public static extern void AddThreadCore(string name);
        [DllImport("LoggerCore.dll", EntryPoint = "InitCore1", CharSet = CharSet.Auto, CallingConvention = CallingConvention.StdCall)]
        public static extern void InitCore1(string path, string name);
        [DllImport("LoggerCore.dll", EntryPoint = "InitCore2", CharSet = CharSet.Auto)]
        public static extern void InitCore2(string path, string name, int maxBuf);
        [DllImport("LoggerCore.dll", EntryPoint = "RunCore", CharSet = CharSet.Auto)]
        public static extern void RunCore();
        [DllImport("LoggerCore.dll", EntryPoint = "DebugCore", CharSet = CharSet.Auto)]
        public static extern void DebugCore(string className, string funName, string message);
        [DllImport("LoggerCore.dll", EntryPoint = "InfoCore", CharSet = CharSet.Auto)]
        public static extern void InfoCore(string className, string funName, string message);
        [DllImport("LoggerCore.dll", EntryPoint = "WarnCore", CharSet = CharSet.Auto)]
        public static extern void WarnCore(string className, string funName, string message);
        [DllImport("LoggerCore.dll", EntryPoint = "ErrorCore", CharSet = CharSet.Auto)]
        public static extern void ErrorCore(string className, string funName, string message);
        [DllImport("LoggerCore.dll", EntryPoint = "FinishCore", CharSet = CharSet.Auto)]
        public static extern void FinishCore();
        static void Main(string[] args)
        {
            InitCore1("log.txt", "ddd");
        }
    }
}
