/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:54:56 by mobonill          #+#    #+#             */
/*   Updated: 2024/11/23 16:24:40 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*void	modify_env_value(t_env *cur, char * limit)
{
	free(cur->value);
	cur->value = ft_strdup(limit + 1);
}

void	create_new_env_node(char *to_compare, t_env *cur, char *limit, char *export)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->content = strdup(export);
	new->name = ft_strdup(to_compare);
	new->value = ft_strdup(limit + 1);
	ft_env_add_back(&cur, new);
}

void	ft_export(char	**export, t_shell *shell)
{
	t_env	*cur;
	int		i;
	char	*limit;
	int		len;
	char	*to_compare;
	bool	exist;

	(void)export;

	i = 1;
	len = 0;
	cur = shell->env;
	while (export[i])
	{
		// if (!ft_strrchr(export[i], '='))
		// {// s'il y a export VAR et pas de = : on stock la variable en attendant une value;
		// 	shell->hidden = malloc(sizeof(t_env));
		// 	shell->hidden->name = ft_strdup(ft_strrchr(export[i], '='));
		// 	//il faut que je add back avec une cpy (voir mes fonctions d'env)
		// 	shell->hidden = shell->hidden->next;
		// }
		exist = false;
		if (ft_strchr(export[i], '=') && exist == false)
		{
			limit = ft_strchr(export[i], '=');
			len = limit - export[i];
			to_compare = ft_strndup(export[i], len);
			while (cur != NULL && cur->next != NULL && export[i])
			{
				if (ft_strcmp(to_compare, cur->name) == 0)
				{
					modify_env_value(cur, limit);
					exist = true;
					break;
				}
				else if (ft_strcmp(to_compare, cur->name) != 0 && exist == false)
					create_new_env_node(to_compare, cur, limit, export[i]);
				cur = cur->next;
			}
			free(to_compare);
		}
	// 	if (limit != NULL)
	// 	{
	// 		while (cur != NULL)
	// 		{
	// 			// limit = ft_strchr(cur->content, '=');
	// 			// if (limit)
	// 			// {
	// 			// 	len = limit - export[i];
	// 			// 	free(cur->value);
	// 			// 	cur->value = ft_strdup(limit + 1);
	// 			// }
	// 			cur = cur->next;
	// 		}
	// 	}
		i++;
	}
	// sort_env_list(cur, shell);
	cur = shell->env;
	while (cur != NULL)
	{
		printf("%s",cur->name);
		printf("=");
		printf("%s\n", cur->value);
		cur = cur->next;
	}
}
void	swap_env(t_env *cur)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = cur->next->name;
	tmp_value = cur->next->value;
	cur->next->name = cur->name;
	cur->next->value = cur->value;
	cur->name = tmp_name;
	cur->value = tmp_value;
}
void	sort_env_list(t_env *cur, t_shell *shell)
{
	t_env	*last;
	bool	check;
	
	cur = shell->env;
	last = NULL;
	check = false;
	while (cur != last && cur->next != last)
	{
		if (check == true)
		{
			cur = shell->env;
			check = false;
		}
		if (ft_strcmp(cur->name, cur->next->name) > 0)
		{
			swap_env(cur); 
			check= true;
		}
		// if (myListIsSorted(shell) == true)
		// 	break;
		cur = cur->next;
	}
	last = cur;
}*/

// bool	myListIsSorted(t_shell *shell)
// {
// 	t_env	*cur;
// 	bool		sorted;

// 	cur = shell->env;
// 	sorted = true;
// 	while (cur->next != NULL)
// 	{
// 		if (ft_strcmp(cur->name, cur->next->name) > 0) {
// 			return (false);
// 		}
// 		cur = cur->next;
// 	}
// 	return (sorted);
// }

// void	add_new_env_variable(char **export, t_shell * shell)
// {

// }

// void	modify_env_variable(char **export, t_shell *shell)
// {

// }

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Структура для переменной окружения
typedef struct s_env
{
    char            *content; // Полная строка переменной окружения ("name=value")
    char            *name;    // Имя переменной
    char            *value;   // Значение переменной
    struct s_env    *next;    // Указатель на следующий узел
}   t_env;

// Структура shell для хранения списка окружения
typedef struct s_shell
{
    t_env   *env; // Список переменных окружения
}   t_shell;

// Прототипы функций вспомогательных библиотек
char    *ft_strdup(const char *s);                 // Дублирует строку
char    *ft_strndup(const char *s, size_t n);      // Дублирует первые n символов строки
char    *ft_strchr(const char *s, int c);          // Находит первый символ c в строке
int     ft_strcmp(const char *s1, const char *s2); // Сравнивает строки
bool    ft_isalpha(int c);                         // Проверяет, является ли символ буквой
bool    ft_isalnum(int c);                         // Проверяет, является ли символ буквой или цифрой

// Добавление узла в конец списка переменных окружения
void ft_env_add_back(t_env **env, t_env *new_node)
{
    if (!*env) // Если список пуст, создаём первый узел
        *env = new_node;
    else
    {
        t_env *cur = *env;
        while (cur->next) // Ищем последний узел
            cur = cur->next;
        cur->next = new_node; // Добавляем новый узел в конец
    }
}

// Проверка валидности идентификатора переменной
bool is_valid_identifier(const char *str)
{
    if (!ft_isalpha(*str) && *str != '_') // Первый символ должен быть буквой или '_'
        return false;
    while (*str) // Проверяем все символы строки
    {
        if (!ft_isalnum(*str) && *str != '_') // Остальные символы должны быть буквами, цифрами или '_'
            return false;
        str++;
    }
    return true; // Идентификатор валиден
}

// Обновление значения существующей переменной
void modify_env_value(t_env *cur, char *limit)
{
    free(cur->value); // Освобождаем старое значение
    cur->value = ft_strdup(limit ? limit + 1 : NULL); // Копируем новое значение
}

// Создание нового узла переменной окружения
void create_new_env_node(char *to_compare, t_env **env, char *limit, char *export)
{
    t_env *new_node = malloc(sizeof(t_env)); // Выделяем память для нового узла
    if (!new_node) // Проверка успешности выделения памяти
        return;
    
    new_node->content = ft_strdup(export); // Копируем полное содержимое переменной
    if (!new_node->content) // Проверка успешности выделения памяти
    {
        free(new_node);
        return;
    }

    new_node->name = ft_strdup(to_compare); // Копируем имя переменной
    if (!new_node->name) // Проверка успешности выделения памяти
    {
        free(new_node->content);
        free(new_node);
        return;
    }

    new_node->value = limit ? ft_strdup(limit + 1) : NULL; // Копируем значение переменной, если оно есть
    new_node->next = NULL; // Новый узел пока не связан с другими

    ft_env_add_back(env, new_node); // Добавляем новый узел в список
}

// Печать отсортированного списка переменных окружения
void print_sorted_env(t_env *env, bool show_values)
{
    while (env) // Проходим по всем узлам
    {
        printf("declare -x %s", env->name); // Выводим имя переменной
        if (show_values && env->value) // Если у переменной есть значение, выводим его
            printf("=\"%s\"", env->value);
        printf("\n");
        env = env->next; // Переходим к следующему узлу
    }
}

// Сортировка списка пузырьковым методом
void swap_env(t_env *cur)
{
    // Меняем местами имя и значение текущего узла и следующего
    char *tmp_name = cur->next->name;
    char *tmp_value = cur->next->value;

    cur->next->name = cur->name;
    cur->next->value = cur->value;
    cur->name = tmp_name;
    cur->value = tmp_value;
}

void sort_env_list(t_env *env)
{
    t_env *last = NULL; // Последний отсортированный элемент
    bool swapped;

    while (env && env->next) // Пока есть элементы для сортировки
    {
        swapped = false; // Флаг указывает, были ли обмены
        while (env->next != last) // Сравниваем текущий узел с его соседом
        {
            if (ft_strcmp(env->name, env->next->name) > 0) // Если порядок нарушен
            {
                swap_env(env); // Меняем узлы местами
                swapped = true;
            }
            env = env->next; // Переходим к следующему узлу
        }
        last = env; // Обновляем последний отсортированный элемент
        env = last ? last->next : env; // Переходим в начало
        if (!swapped) // Если обменов не было, сортировка завершена
            break;
    }
}

// Освобождение памяти для списка окружения
void free_env_list(t_env *env)
{
    t_env *tmp;

    while (env) // Проходим по всем узлам
    {
        tmp = env;
        env = env->next;
        free(tmp->name);   // Освобождаем память для имени
        free(tmp->value);  // Освобождаем память для значения
        free(tmp->content); // Освобождаем полное содержимое
        free(tmp);         // Освобождаем сам узел
    }
}

// Обработка новой или существующей переменной
void handle_new_or_existing_env(char *to_compare, char *limit, char *export, t_env **env)
{
    t_env *cur = *env;
    bool exist = false;

    while (cur) // Проверяем, существует ли переменная с таким именем
    {
        if (ft_strcmp(to_compare, cur->name) == 0) // Если имя совпадает
        {
            modify_env_value(cur, limit); // Обновляем значение
            exist = true;
            break;
        }
        cur = cur->next; // Переходим к следующему узлу
    }
    if (!exist) // Если переменная не найдена
        create_new_env_node(to_compare, env, limit, export); // Создаём новую переменную
}

// Реализация команды export
void ft_export(char **export, t_shell *shell)
{
    t_env *cur = shell->env;
    char *limit;
    char *to_compare;
    int i = 1;

    while (export[i]) // Обрабатываем каждый аргумент
    {
        if (!is_valid_identifier(export[i])) // Проверяем валидность идентификатора
        {
            fprintf(stderr, "export: `%s': not a valid identifier\n", export[i]); // Выводим ошибку
            i++;
            continue;
        }

        limit = ft_strchr(export[i], '='); // Ищем "=" в аргументе
        if (limit) // Если найдено "="
        {
            to_compare = ft_strndup(export[i], limit - export[i]); // Извлекаем имя переменной
            handle_new_or_existing_env(to_compare, limit, export[i], &shell->env); // Обрабатываем переменную
            free(to_compare);
        }
        else // Если "=" нет
        {
            to_compare = ft_strdup(export[i]); // Копируем имя переменной
            handle_new_or_existing_env(to_compare, NULL, export[i], &shell->env); // Создаём или обновляем переменную
            free(to_compare);
        }
        i++;
    }

    sort_env_list(shell->env); // Сортируем список переменных

    if (!export[1]) // Если команда вызвана без аргументов
        print_sorted_env(shell->env, true); // Выводим список переменных
}
