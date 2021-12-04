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
        [DllImport("Termi.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int a, int b);
        public static void Main(string[] args)
        {
            int number1;
            int number2;

            Console.WriteLine("Enter value of int a and int b: ");
            number1 = Convert.ToInt32(Console.ReadLine());
            number2 = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine("Sum is: " + Add(number1, number2));
        }
    }
}