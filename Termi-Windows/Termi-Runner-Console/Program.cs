using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;

namespace Termi_Runner_Console
{
    class Program
    {
        [DllImport("Termi.dll", EntryPoint = "Welcome", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Welcome();

        public static string path = Directory.GetCurrentDirectory();

        public static void Main(string[] args)
        {
            Functions.Clear();
            Console.WriteLine(path);
            Console.WriteLine(" ");
            Console.WriteLine("Starting Termi...\nPlease wait...");
            Thread.Sleep(1000);

            Functions.Clear();

            Welcome();
            Input.Input_Main();

            Console.ReadLine();
        }
    }
}