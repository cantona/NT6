// tail.c
// by Find.

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string file,content,*output;
        int n = 24,i;

          if (! SECURITY_D->valid_grant(me, "(wizard)")) 
                return 0; 
        seteuid(geteuid(me));
        if(!arg)
                return help(me);

        if(sscanf(arg,"-%d %s",n, arg) == 2)
                if(n<1)
                        n = 1;

        file=resolve_path(query("cwd", me),arg);
        if( file_size(file)<0 )
                return notify_fail("沒有這個檔案。\n");

        if(!content = read_file(file))
                return notify_fail("你沒有讀取這個檔案內容的權限。\n");

        output = explode(content,"\n");
        i = sizeof(output);

        me->start_more(implode(output[(i>n?i-n:0)..],"\n")+"\n");
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 :

tail <檔案>

此指令可讓你直接讀取某檔案最末尾的幾行。

tail -n <檔案>

此指令可讓你直接讀取某檔案最末尾的 n 行。(n 為正整數)

HELP
    );
    return 1;
}