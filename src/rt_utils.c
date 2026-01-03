#include "rt_utils.h"
#include "libft.h"
#include <stdint.h>
#include <stdbool.h>

static uint64_t	random_uint64(void)
{
	static uint64_t x = 0x629d97afad9281f2; // /bin/bash -c openssl rand -hex 8
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	return (x);
}

double random_double(double min, double max)
{
	uint64_t u = random_uint64() >> 11;
	double v = (double)u * (1.0 / 9007199254740992.0);
	return (min + (max - min) * v);
}

int	random_int(int min, int max)
{
	if (min > max)
		return (min);
	int	range = max - min + 1;
	return (min + (int)(random_double(0.0, 1.0) * range));
}

double clamp(double x, double min, double max)
{
	if (x < min)
		return min;
	if (x > max)
		return max;
	return (x);
}

double	pow2(double a)
{
	return (a * a);
}

/*
@brief spaceがなかった時false
*/
int	skip_spaces(char **ptr)
{
	if (**ptr != ' ' && **ptr != '\t')
		return (EXIT_FAILURE);
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	return (EXIT_SUCCESS);
}

int	skip_digit(char **ptr)
{
	if (**ptr == '-' || **ptr == '+')
		(*ptr)++;
	if (!ft_isdigit(**ptr))
		return (EXIT_FAILURE);
	while (ft_isdigit(**ptr))
		(*ptr)++;
	return (EXIT_SUCCESS);
}

/*
@brief validateする際にvecの情報が正しく入力されているか確認する関数
@param is	IS_COLORのとき、0 - 255の範囲内に収まっているか確認
@param is	IS_UNITのとき、ベクトルの長さが1かどうか確認
@param is	IS_POINTのとき、正しい座標かどうか確認
*/
int	skip_vec(char **ptr, t_is is)
{
	size_t	i;
	double	d_tmp;
	char	*tmp_ptr;

	i = 0;
	d_tmp = 0;
	while (i++ < 3)
	{
		tmp_ptr = *ptr;
		if (is == IS_UNIT)
			d_tmp += pow2(ft_strtod(*ptr, ptr));
		else
			d_tmp = ft_strtod(*ptr, ptr);
		if (tmp_ptr == *ptr)
			return (EXIT_FAILURE);
		if (is == IS_COLOR)
		{
			if (d_tmp < 0 || 255 < d_tmp)
				return (EXIT_FAILURE);
		}
		if (i != 3 && *((*ptr)++) != ',')
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
@brief 単方向リストline_lstを探索して先頭文字がwordの文字列を返す
最後のスペースはスキップする
*/
char	*get_word_line(t_list *line_lst, const char *word)
{
	char	*line;
	size_t	word_len;

	line = NULL;
	word_len = ft_strlen(word);
	while (line_lst)
	{
		line = (char *)line_lst->content;
		if (ft_strncmp(line, word, word_len) == 0)
			break ;
		line_lst = line_lst->next;
	}
	if (!line)
		return (NULL);
	line += word_len;
	skip_spaces(&line);
	return (line);
}

/*
@brief validate用の関数
@brief lineの数字が[min,max]の範囲内のときtrue
*/
bool	skip_range(char **line, double min, double max)
{
	double	d_tmp;

	d_tmp = ft_strtod(*line, line);
	return (min <= d_tmp && d_tmp <= max);
}

/*
@brief 度数法を弧度法に変換
*/
double	to_radians(const double degrees)
{
	return (degrees * M_PI / 180.0);
}
