/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:12:17 by ozamora-          #+#    #+#             */
/*   Updated: 2024/11/22 15:22:46 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static int	word_len(char const *s, char c)
{
	int	w_len;

	w_len = 0;
	while (s[w_len] != '\0' && s[w_len] != c)
		w_len++;
	return (w_len);
}

static int	free_words(char **split, int i)
{
	if (!split[i])
	{
		while (i > 0)
			free(split[--i]);
		free(split);
		return (1);
	}
	else
		return (0);
}

static char	**split_aux(char const *s, char c, char **split, int word_counter)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	while (i < word_counter)
	{
		while (s[start] != '\0' && s[start] == c)
			start++;
		split[i] = ft_substr(s, start, word_len(s + start, c));
		if (free_words(split, i))
			return (NULL);
		while (s[start] != '\0' && s[start] != c)
			start++;
		i++;
	}
	split[word_counter] = NULL;
	return (split);
}

/**
 * ft_split - Splits a string into an array of substrings using a delimiter.
 * 
 * @s:   The string to be split.
 * @c:   The delimiter character.
 * 
 * Return: A pointer to an array of strings (substrings created from 's'). 
 *         Each element in the array represents a substring found between 
 *         occurrences of 'c'. 
 *         The array is NULL-terminated.
 *         Returns NULL if the memory allocation fails or if 's' is NULL.
 * 
 * Notes:
 * - Consecutive delimiters are treated as a single delimiter.
 * - Leading and trailing delimiters are ignored, meaning they do not contribute 
 * to the creation of empty strings.
 * - The caller is responsible for freeing the memory allocated for the array and
 * its substrings.
 */
char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_counter;

	if (!s)
		return (NULL);
	word_counter = count_words(s, c);
	split = (char **)malloc((word_counter + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = split_aux(s, c, split, word_counter);
	return (split);
}

// int	main(void)
// {
// 	char const	*str = "Hello world! This is a test.";
// 	char		delimiter = ' ';
// 	char		**words = ft_split(str, delimiter);
// 	int			i;

// 	if (words)
// 	{
// 		for (int i = 0; words[i] != NULL; i++) {
// 			printf("%s\n", words[i]);
// 			free(words[i]); 
// 		}
// 		free(words); 
// 	}
// 	return 0;
// }