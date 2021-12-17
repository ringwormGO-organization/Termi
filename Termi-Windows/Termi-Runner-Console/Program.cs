using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace Termi_Runner_Console
{
    class Program
    {
        [DllImport("Termi.dll", EntryPoint = "Welcome", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Welcome();

        [DllImport("Termi.dll", EntryPoint = "Terminal", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terminal();

        public static void Main(string[] args)
        {
            Welcome();

            Terminal();

            Console.ReadLine();
        }
    }
}