using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.IO;

namespace Termi_Runner_Console
{
    class Input
    {
        [DllImport("Termi.dll", EntryPoint = "Help", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Help();

        public static void Input_Main()
        {
            while (true)
            {
                Console.Write("Termi> ");
                Input_Start();
            }
        }

        private static void Input_Start()
        {
            string input;

            input = Console.ReadLine();

            if (input == "help")
            {
                Help();
            }
            else if (input == "exit")
            {
                Functions.Exit();
            }
            else
            {
                Console.WriteLine("Command invalid");
            }
        }
    }
}