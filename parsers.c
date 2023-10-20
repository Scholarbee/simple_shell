#include "sshell.h"



char **par_strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **string_array;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!conv_is_delim(str[i], d) && (conv_is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	string_array = malloc((1 + numwords) * sizeof(char *));
	if (!string_array)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (conv_is_delim(str[i], d))
			i++;
		k = 0;
		while (!conv_is_delim(str[i + k], d) && str[i + k])
			k++;
		string_array[j] = malloc((k + 1) * sizeof(char));
		if (!string_array[j])
		{
			for (k = 0; k < j; k++)
				free(string_array[k]);
			free(string_array);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			string_array[j][m] = str[i++];
		string_array[j][m] = 0;
	}
	string_array[j] = NULL;
	return (string_array);
}


char **par_strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **string_arr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	string_arr = malloc((1 + numwords) * sizeof(char *));
	if (!string_arr)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		string_arr[j] = malloc((k + 1) * sizeof(char));
		if (!string_arr[j])
		{
			for (k = 0; k < j; k++)
				free(string_arr[k]);
			free(string_arr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			string_arr[j][m] = str[i++];
		string_arr[j][m] = 0;
	}
	string_arr[j] = NULL;
	return (string_arr);
}
