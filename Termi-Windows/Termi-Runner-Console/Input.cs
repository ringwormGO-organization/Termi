﻿using System;
using System.Runtime.InteropServices;
using System.IO;

namespace Termi_Runner_Console
{
    class Input
    {
        [DllImport("Termi.dll", EntryPoint = "Floppy", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Floppy();

        [DllImport("Termi.dll", EntryPoint = "Calculator", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Calculator();

        [DllImport("Termi.dll", EntryPoint = "  GeoCalc", CallingConvention = CallingConvention.Cdecl)]
        public static extern void GeoCalc();

        [DllImport("Termi.dll", EntryPoint = "Help", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Help();

        [DllImport("Termi.dll", EntryPoint = "Filesystem", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Filesystem();

        /* ---------------------------------------------------------------------------------------- */

        public static string TermiString = "Termi> ";

        public static void Input_Start()
        {
            while (true)
            {
                Console.Write(TermiString);
                Input_Main();
            }
        }

        private static void Input_Main()
        {
            string input;

            input = Console.ReadLine();
            Input_Check(input);
        }

        private static void Input_Check(string input)
        {
            switch (input)
            {
                case "help":
                    Help();
                    break;

                case "floppy":
                    Floppy();
                    break;

                case "calculator":
                    Calculator();
                    break;

                case "geo-calc":
                    GeoCalc();
                    break;

                case "filesys":
                    Filesystem();
                    break;

                case "filesys-mkdir":
                    Console.Write("Type a path to create directory: ");
                    string path = Console.ReadLine();

                    if (path == "")
                    {
                        path = Directory.GetCurrentDirectory();
                    }

                    Directory.CreateDirectory(path);
                    break;

                case "clear" or "cls":
                    Functions.Clear();
                    break;

                case "exit":
                    Functions.Exit();
                    break;

                default:
                    if (input.Length > 0) //if enter is pressed, do nothing
                    {
                        Console.WriteLine("Command invalid");
                    }
                    break;
            }  
        }
    }
}