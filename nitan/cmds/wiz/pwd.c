// pwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());

        write("Cwd:"+query("cwd", me)+"\n");
        write("Cwf:"+query("cwf", me)+"\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : pwd
 
這個指令會顯示出你目前的工作目錄 (cwd) 及工作檔案 (cwf).
'update' 不加參數時便會更新你的 cwf.
 
HELP );
    return 1;
}