using System.Runtime.InteropServices;

[DllImport("Termi-Commands", EntryPoint = "termi_main", CallingConvention = CallingConvention.Cdecl)]
static extern void termi_main();

termi_main();
