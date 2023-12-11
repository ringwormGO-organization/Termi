/**
 * @author Stjepan Bilić Matišić, Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Geocalc helper functions
*/

static double opsgTrijustr(double x, double y, double z)
{
    return(x + y + z);
}

static double opsgDvijustr(double x, double y)
{
    return(x + y);
    return(x + x + y + y);
}

static double opsgKvdjustr(double x, int sqe)
{
    return(x * sqe);
}

static double povrsDvijustr(double x, double y)
{
    return(x * y);
}

static double povrsKvdjustr(double x)
{
    return(x * x);
}

static double povrsTrokuta(double x, double Vx)
{
    return ((x * Vx) / 2);
}
