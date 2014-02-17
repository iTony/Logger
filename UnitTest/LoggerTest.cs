using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using LoggerCsharp;

namespace UnitTest
{
    public class LoggerTest
    {
        public void AddThreadTest(string path, string threadName,string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.AddThread(threadName);
            logger.Debug(message);
            logger.Finish();
            string msg = " Debug [" + threadName + "] UnitTest.LoggerTest(AddThreadTest) " + message;
            StreamReader sr = File.OpenText(path);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void DebugTest(string path,string message,out string result)
        {
            
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();

//             DateTime dt = DateTime.Now;
//             string time = dt.ToString("yyyy-MM-dd hh:mm:ss.fff");
            logger.Debug(message);
            logger.Finish();
             
            string msg = " Debug [MainThread] UnitTest.LoggerTest(DebugTest) " + message;
            StreamReader sr = File.OpenText(path);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
            //logger
        }
        
        public void DebugTimeTest(string path,string message,out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Debug(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%t");
            string msg = " Debug [MainThread] UnitTest.LoggerTest(DebugTimeTest) " + message;
            string actpath = path.Substring(0, index) + time + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
            //logger
        }

        public void SoftWareNameTest(string path, string message,string softwareName, out string result)
        {

            Logger logger = Logger.GetLogger();
            logger.Init(path, softwareName);
            logger.Run();
            //logger.Debug(message);
            logger.Finish();

            string msg = " [1.0.0.1] [" + softwareName + "] [Windows XP Professionel 32bits Service Pack 3]";
            StreamReader sr = File.OpenText(path);
            //sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
            //logger
        }

        public void DebugNumberTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Debug(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            //string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%d");
            string msg = " Debug [MainThread] UnitTest.LoggerTest(DebugNumberTest) " + message;
            string actpath = path.Substring(0, index) + "0" + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void InfoTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();

            //             DateTime dt = DateTime.Now;
            //             string time = dt.ToString("yyyy-MM-dd hh:mm:ss.fff");
            logger.Info(message);
            logger.Finish();

            string msg = " Info [MainThread] UnitTest.LoggerTest(InfoTest) " + message;
            StreamReader sr = File.OpenText(path);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void InfoTimeTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Info(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%t");
            string msg = " Info [MainThread] UnitTest.LoggerTest(InfoTimeTest) " + message;
            string actpath = path.Substring(0, index) + time + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void InfoNumberTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Info(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            //string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%d");
            string msg = " Info [MainThread] UnitTest.LoggerTest(InfoNumberTest) " + message;
            string actpath = path.Substring(0, index) + "0" + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void WarnTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();

            //             DateTime dt = DateTime.Now;
            //             string time = dt.ToString("yyyy-MM-dd hh:mm:ss.fff");
            logger.Warn(message);
            logger.Finish();

            string msg = " Warn [MainThread] UnitTest.LoggerTest(WarnTest) " + message;
            StreamReader sr = File.OpenText(path);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void WarnTimeTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Warn(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%t");
            string msg = " Warn [MainThread] UnitTest.LoggerTest(WarnTimeTest) " + message;
            string actpath = path.Substring(0, index) + time + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void WarnNumberTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Warn(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            //string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%d");
            string msg = " Warn [MainThread] UnitTest.LoggerTest(WarnNumberTest) " + message;
            string actpath = path.Substring(0, index) + "0" + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void ErrorTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Error(message);
            logger.Finish();

            string msg = " Error [MainThread] UnitTest.LoggerTest(ErrorTest) " + message;
            StreamReader sr = File.OpenText(path);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void ErrorTimeTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Error(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%t");
            string msg = " Error [MainThread] UnitTest.LoggerTest(ErrorTimeTest) " + message;
            string actpath = path.Substring(0, index) + time + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

        public void ErrorNumberTest(string path, string message, out string result)
        {
            Logger logger = Logger.GetLogger();
            logger.Init(path);
            logger.Run();
            logger.Error(message);
            logger.Finish();
            DateTime dt = DateTime.Now;
            //string time = dt.ToString("yyyyMMddHHmmss");
            int index = path.IndexOf("%d");
            string msg = " Error [MainThread] UnitTest.LoggerTest(ErrorNumberTest) " + message;
            string actpath = path.Substring(0, index) + "0" + path.Substring(index + 2);
            StreamReader sr = File.OpenText(actpath);
            sr.ReadLine();
            string log = sr.ReadLine();
            log = log.Substring(23);
            if (msg.Equals(log))
            {
                result = "Right";
            }
            else
            {
                result = log;
            }
        }

    }
}
