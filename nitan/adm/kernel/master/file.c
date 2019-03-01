// This program is a part of NT MudLIB

string creator_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "creator_file", str);
}

// 判斷一個指定物件所屬的區域
string domain_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "domain_file", str);
}

// 判斷一個指定物件的作者為誰
// 需定義 PACKAGE_MUDLIB_STATS
string author_file(string str)
{
        return (string)call_other(SIMUL_EFUN_OB, "author_file", str);
}

// 為新創造的物件指定一個隱私字串
// 需定義 PRIVS
string privs_file(string filename)
{
        return filename;
}
