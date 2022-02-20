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
        [DllImport("Termi.dll", EntryPoint = "Calculator", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Calculator(double num1, char operation, double num2);

        [DllImport("Termi.dll", EntryPoint = "Help", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Help();

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

                case "calculator":
                    Applications.Calc.CalculatorLogic();
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