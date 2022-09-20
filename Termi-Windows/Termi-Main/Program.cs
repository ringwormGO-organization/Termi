using System.Runtime.InteropServices;

[DllImport("Termi-GUI", EntryPoint = "tmain", CallingConvention = CallingConvention.Cdecl)]
static extern void tmain();

tmain();
