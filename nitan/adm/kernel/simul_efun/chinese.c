
string chinese_number(int i)
{
        return CHINESE_D->chinese_number(i);
}

string to_chinese(string str)
{
        return CHINESE_D->chinese(str);
}

private int chars_are_folow_uni(string str)
{
	string chars = str;
	int len = strlen(chars);

	for (int i = 0; i < len;) {
		if ((chars[i] >> 6) != 0x2)
			return 0;
		i++;
	}
        return 1;
}

int is_chinese(string str)
{
	string key = str;
	int required_len;

	return 1;

	if (key[0] >> 7 == 0)
		required_len = 1;
	else if (key[0] >> 5 == 0x6)
		required_len = 2;
	else if (key[0] >> 4 == 0xE)
		required_len = 3;
	else if (key[0] >> 5 == 0x1E)
		required_len = 4;
	else
		return 0;

	return (strlen(key) == required_len && chars_are_folow_uni(key + 1));
}

#if 0
int is_chinese(string str)
{
        int i;

        if( strlen(str) < 2 ) return 0;

        for( i = 0; i < strlen(str); i++ ) {
                if( str[i] < 161 || str[i] == 255 ) return 0;
                if( !(i % 2) && (str[i] < 176 || str[i] >= 248) ) return 0;
        }

        return 1;
}
#endif

/*
int is_chinese(string str)
{
        if (strlen(str) < 2) return 0;
        if (str[0] < 176 || str[0] > 247) return 0;
        if (str[1] < 161 || str[1] > 254) return 0;
        if (str[0] == 215 && str[1] > 249) return 0;
        return 1;
}
*/

string time_period(int time)
{
        int t, d, h, m, s;
        string str;

        t = time;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;

        if( d ) str = chinese_number(d) + "天";
        else str = "";

        if( h ) str += chinese_number(h) + "小時";
        if( m ) str += chinese_number(m) + "分";
        str += chinese_number(s) + "秒";

        return str;
}
