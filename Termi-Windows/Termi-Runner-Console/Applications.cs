using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Termi_Runner_Console
{
    class Applications
    {
        public static class Calc
        {
            [DllImport("Termi.dll", EntryPoint = "Calculator", CallingConvention = CallingConvention.Cdecl)]
            public static extern void Calculator(double num1, char operation, double num2);

            public static void CalculatorLogic()
            {
                Console.WriteLine("Type numbers and operation to continue execution of calculator\n" +
                        "Type 'x' to exit calculator.");
                double number1 = Convert.ToDouble(Console.ReadLine());
                char operation = Convert.ToChar(Console.ReadLine());
                double number2 = Convert.ToDouble(Console.ReadLine());

                try
                {
                    Calculator(number1, operation, number2);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }
        }
    }
}
