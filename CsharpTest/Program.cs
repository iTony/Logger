using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LoggerCsharp;
using System.Threading;

namespace CsharpTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Logger logger = Logger.GetLogger();
            logger.Init("E:\\Test\\Log\\csharplog%t%000d.txt");
            logger.Run();
            logger.Info("ddd");
            logger.Debug("hello world");
            Thread t = new Thread(new ThreadStart(ThreadProc));
            Thread t1 = new Thread(new ThreadStart(ThreadProc1));
            Thread t2 = new Thread(new ThreadStart(ThreadProc));
            Thread t3 = new Thread(new ThreadStart(ThreadProc));
            t.Start();
             t1.Start();
//             t2.Start();
//             t3.Start();
            t.Join();
             t1.Join();
//             t2.Join();
//             t3.Join();
            logger.Finish();
            //Console.ReadKey();
        }

        private static void ThreadProc()
        {
            Logger logger = Logger.GetLogger();
            logger.AddThread("thread");
            for (int i = 0; i < 5; i++)
            {
                //Console.WriteLine("ThreadPorc:{0}", i);
                logger.Info("ThreadPorc: world");
                Thread.Sleep(100);
            }
        }
        private static void ThreadProc1()
        {
            Logger logger = Logger.GetLogger();
            logger.AddThread("thread123");
            for (int i = 0; i < 5; i++)
            {
                //Console.WriteLine("ThreadPorc:{0}", i);
                logger.Info("ThreadPorc1: hello");
                Thread.Sleep(100);
            }
        }
    }
}
