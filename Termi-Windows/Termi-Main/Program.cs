using System.Runtime.InteropServices;

[DllImport("Termi-GUI.dll", EntryPoint = "tmain", CallingConvention = CallingConvention.Cdecl)]
static extern void tmain();

tmain();
