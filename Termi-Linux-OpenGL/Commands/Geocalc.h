/**
 * @author StjepanBM1
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Geocalc helper functions
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
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