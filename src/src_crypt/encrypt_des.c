#include "ft_ssl_crypt.h"
#include "crypt.h"


int         init_block(char *pt, t_block *block)
{
    //Initial Permutation
    pt = permute(pt, g_initial_perm, 64);
    //ft_printf("after initial permutation = %s\n", pt);
    return (split(pt, &(block->left), &(block->right), 32));
}

char        *final_text(t_block *bk)
{
    char *concat;
    char *cipher;

    //Combination 
    concat = ft_strjoin(bk->left, bk->right);
    //clean
    //free(bk->right);
    //free(bk->left); 
    //Final Permutation
    cipher = permute(concat, g_final_perm, 64);
    return (cipher);
}

int             s_boxes(char *x, char **op)
{
    int     i;
    int     j;
    t_array arr;

    i = -1;
    j = 0;
    while(++i < 8)
    {
        arr.row = 2 * (int)(x[i * 6] - '0') + (int)(x[i * 6 + 5] - '0');
        arr.col = 8 * (int)(x[i * 6 + 1] - '0') + 4 * (int)(x[i * 6 + 2] - '0') \
            +  2 * (int)(x[i * 6 + 3] - '0') + (int)(x[i * 6 + 4] - '0');
        arr.val = g_s[i][arr.row][arr.col];
        (*op)[j]= arr.val / 8 + '0';
        arr.val %= 8;
        (*op)[j + 1]= arr.val / 4 + '0';
        arr.val %= 4;
        (*op)[j + 2]= arr.val / 2 + '0';
        arr.val %= 2;
        (*op)[j + 3]= arr.val + '0';
        j += 4;
    }
    return (1);
}

int             crypt_function(char *round_key, t_block *bk, int i)
{
    char    *tmp;
    char    *op;

    //Expansion D-box
    if (!(tmp = ft_strdup(bk->right)))
        return (0); 
    bk->right = permute(bk->right, g_exp_d, 48);
    //XOR RoundKey[i] and right_expanded
    bk->right = xor_function(round_key, bk->right);
    //S-boxes
    if (!(op = malloc(33)))
        return (0);
    op[32] = '\0';
    if (!s_boxes(bk->right, &op))
        return (0);
    //free(bk->right);
    //Straight D-box
    op = permute(op, g_per, 32);
    //XOR left and op
    bk->right = xor_function(op, bk->left);
    bk->left = tmp;
    if (i == 15)
    {
        tmp = bk->left;
        bk->left = bk->right;
        bk->right = tmp; 
    }
    return (1);
}

static void     treat_block(char **text)
{
    char    *text_block;
    int     len;

    if (!(text_block = malloc(9)))
        return ;
    text_block[8] = '\0';
    len = ft_strlen(*text);
    if (len >= 8)
    {
        ft_strncpy(text_block, *text, 8);
        *text = text_block;
        return ;
    }
    ft_strcpy(text_block, *text);
    while (len < 8)
        text_block[len++] = 8 - ft_strlen(*text);
    *text = text_block;
}

char            *encrypt_des(char *pt, char *key)
{
    t_key   k;
    t_block bk;
    int     i;
    char    *round_key;

    treat_block(&pt);
    if (!keygen(&key) || !(split(key, &(k.left), &(k.right), 28)) || !init_block(dec2bin(pt), &bk))
        return (NULL);
    i = -1;
    while (++i < 16)
    { 
        round_key = round_key_function(&(k.left), &(k.right), g_shift_table[i]);
        if (!crypt_function(round_key, &bk, i))
            return (NULL);
    }
    return (final_text(&bk));
}