__END_DECLS int key_to_index (int key)
{
    if (key >= '0' && key <= '9')
	return (int) (key - '0');
    else if (key >= 'a' && key <= 'c')
	return (int) (key - 'a') + 10;
    else if (key >= 'e' && key <= 'f')
	return (int) (key - 'e') + 13;
    else
	return -100;
}

char index_to_key (int index)
{
    if (index >= 0 && index <= 9)
	return (char) (index + '0');
    else if (index >= 10 && index <= 12)
	return (char) (index - 10 + 'a');
    else if (index >= 13 && index <= 14)
	return (int) (index - 13 + 'e');
    else
	/* huh? */
	return '?';
}

int main (void)
{
    int i;
    for (i = 0; i < 16; i++) {
	printf ("%d ==> %c:%d\n", i, index_to_key (i), key_to_index (index_to_key (i)));
    }
}
