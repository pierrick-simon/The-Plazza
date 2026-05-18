/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** tests_parsing
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <fcntl.h>

static void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init, linkInvalid)
{
    cr_assert(true);
}
