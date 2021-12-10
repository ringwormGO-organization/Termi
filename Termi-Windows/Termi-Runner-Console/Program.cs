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
        [DllImport("Termi.dll", EntryPoint = "Add", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int a, int b);

        [DllImport("Termi.dll", EntryPoint = "Minus", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Minus(int a, int b);

        [DllImport("Termi.dll", EntryPoint = "Terminal", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Terminal();

        public static void Main(string[] args)
        {
            Terminal();

            Console.ReadLine();
        }
    }
}