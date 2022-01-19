using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Security.Principal;
using System.Threading;

namespace Termi_Runner_Console
{
    class Program
    {
        [DllImport("Termi.dll", EntryPoint = "Welcome", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Welcome();

        [DllImport("shell32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool IsUserAnAdmin();

        public static string path = Directory.GetCurrentDirectory();

        public static void IsAdministrator()
        {
            /*var identity = WindowsIdentity.GetCurrent();
            var principal = new WindowsPrincipal(identity);*/
            if (!IsUserAnAdmin())
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("You need to run this application by administrator!");
                Thread.Sleep(4000);
                Environment.Exit(0);
            }
            else
            {
                Console.WriteLine("Application have administartor privilges");
                Thread.Sleep(1000);
            }
        }

        public static void Main(string[] args)
        {
            IsAdministrator();

            Functions.Clear();
            Console.WriteLine(path + "\n");
            Console.WriteLine("Starting Termi...\nPlease wait...");
            Thread.Sleep(1000);

            Functions.Clear();

            Welcome();
            Input.Input_Start();

            Console.ReadLine();
        }
    }
}