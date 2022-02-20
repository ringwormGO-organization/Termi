using System;

namespace Termi_Runner_Console
{
    class Functions
    {
        public static void Beep()
        {
            Console.Beep();
        }

        public static void Clear()
        {
            Console.Clear();
        }

        public static void Exit()
        {
            Environment.Exit(0);
        }

        public static void Exit(int code)
        {
            Environment.Exit(code);
        }
    }
}