/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** main
*/

void get_name()
{
    std::string name;
    std::cout << "What is your name? ";
    std::getline(std::cin, name);
    std::cout << "Hello " << name << std::endl;
}

int main(int ac, char **av)
{
    if (!check_error(ac, av))
        return 84;
    test_regex(av[1]);
    get_name();
    return 0;
}