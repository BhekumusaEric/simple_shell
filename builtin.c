#include "shell.h"
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_change_directory(char **args, char __attribute__((__unused__)) **front);
int shellby_display_help(char **args, char __attribute__((__unused__)) **front);

/**
 *  * get_builtin - Retrieve a pointer to a built-in function based on the command.
 *   * @command: The command to match.
 *    *
 *     * Return: A function pointer to the corresponding built-in function.
 *      */
int (*get_builtin(char *command))(char **args, char **front)
{
		builtin_t funcs[] = {
					{ "exit", shellby_exit },
							{ "env", shellby_env },
									{ "setenv", shellby_setenv },
											{ "unsetenv", shellby_unsetenv },
													{ "cd", shellby_change_directory },
															{ "alias", shellby_alias },
																	{ "help", shellby_display_help },
																			{ NULL, NULL }
						};
			int i;

				for (i = 0; funcs[i].name; i++)
						{
									if (_strcmp(funcs[i].name, command) == 0)
													break;
										}
					return (funcs[i].f);
}

/**
 *  * shellby_exit - Terminate the shellby process with an optional exit status.
 *   * @args: An array of arguments, which may include the exit status.
 *    * @front: A double pointer to the start of the arguments array.
 *     *
 *      * Return: If no arguments are provided, return -3.
 *       *         If an invalid exit value is given, return 2.
 *        *         Otherwise, exit the program with the provided status value.
 *         *
 *          * Description: If -3 is returned, the program exits to the main function.
 *           */
int shellby_exit(char **args, char **front)
{
		int i, int_length = 10;
			unsigned int exit_status = 0, max_value = 1 << (sizeof(int) * 8 - 1);

				if (args[0])
						{
									if (args[0][0] == '+')
												{
																i = 1;
																			int_length++;
																					}
											for (; args[0][i]; i++)
														{
																		if (i <= int_length && args[0][i] >= '0' && args[0][i] <= '9')
																							exit_status = (exit_status * 10) + (args[0][i] - '0');
																					else
																										return (create_error(--args, 2));
																							}
												}
					else
							{
										return (-3);
											}
						if (exit_status > max_value - 1)
									return (create_error(--args, 2));
							args -= 1;
								free_args(args, front);
									free_env();
										free_alias_list(aliases);
											exit(exit_status);
}

/**
 *  * shellby_change_directory - Change the current directory of the shellby process.
 *   * @args: An array of arguments.
 *    * @front: A double pointer to the start of the arguments array.
 *     *
 *      * Return: If the provided string is not a directory, return 2.
 *       *         If an error occurs, return -1.
 *        *         Otherwise, return 0.
 *         */
int shellby_change_directory(char **args, char __attribute__((__unused__)) **front)
{
		char **directory_info, *new_line = "\n";
			char *old_pwd = NULL, *current_pwd = NULL;
				struct stat directory;

					old_pwd = getcwd(old_pwd, 0);
						if (!old_pwd)
									return (-1);

							if (args[0])
									{
												if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
															{
																			if ((args[0][1] == '-' && args[0][2] == '\0') ||
																										args[0][1] == '\0')
																							{
																												if (_getenv("OLDPWD") != NULL)
																																		(chdir(*_getenv("OLDPWD") + 7));
																															}
																						else
																										{
																															free(old_pwd);
																																			return (create_error(args, 2));
																																						}
																								}
														else
																	{
																					if (stat(args[0], &directory) == 0 && S_ISDIR(directory.st_mode)
																												&& ((directory.st_mode & S_IXUSR) != 0))
																										chdir(args[0]);
																								else
																												{
																																	free(old_pwd);
																																					return (create_error(args, 2));
																																								}
																										}
															}
								else
										{
													if (_getenv("HOME") != NULL)
																	chdir(*(_getenv("HOME")) + 5);
														}

									current_pwd = getcwd(current_pwd, 0);
										if (!current_pwd)
													return (-1);

											directory_info = malloc(sizeof(char *) * 2);
												if (!directory_info)
															return (-1);

													directory_info[0] = "OLDPWD";
														directory_info[1] = old_pwd;
															if (shellby_setenv(directory_info, directory_info) == -1)
																		return (-1);

																directory_info[0] = "PWD";
																	directory_info[1] = current_pwd;
																		if (shellby_setenv(directory_info, directory_info) == -1)
																					return (-1);
																			if (args[0] && args[0][0] == '-' && args[0][1] != '-')
																					{
																								write(STDOUT_FILENO, current_pwd, _strlen(current_pwd));
																										write(STDOUT_FILENO, new_line, 1);
																											}
																				free(old_pwd);
																					free(current_pwd);
																						free(directory_info);
																							return (0);
}

/**
 *  * shellby_display_help - Show information about shellby built-in commands.
 *   * @args: An array of arguments.
 *    * @front: A pointer to the start of the arguments array.
 *     *
 *      * Return: If an error occurs, return -1.
 *       *         Otherwise, return 0.
 *        */
int shellby_display_help(char **args, char __attribute__((__unused__)) **front)
{
		if (!args[0])
					help_all();
			else if (_strcmp(args[0], "alias") == 0)
						help_alias();
				else if (_strcmp(args[0], "cd") == 0)
							help_cd();
					else if (_strcmp(args[0], "exit") == 0)
								help_exit();
						else if (_strcmp(args[0], "env") == 0)
									help_env();
							else if (_strcmp(args[0], "setenv") == 0)
										help_setenv();
								else if (_strcmp(args[0], "unsetenv") == 0)
											help_unsetenv();
									else if (_strcmp(args[0], "help") == 0)
												help_help();
										else
													write(STDERR_FILENO, name, _strlen(name));

											return (0);
}

