using System.Runtime.InteropServices;

Console.WriteLine("Hello World!");

[DllImport("Termi-GUI.dll", EntryPoint = "tmain", CallingConvention = CallingConvention.Cdecl)]
static extern void tmain();

tmain();

Console.ReadLine();
