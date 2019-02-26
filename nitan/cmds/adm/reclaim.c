// claim.c

inherit F_CLEAN_UP;

int filter(object ob);

int main(object me, string arg)
{
        object *ob;
        int i;
        int n;

//#if 0
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
//#endif

        write(sprintf("一共清除了 %d 個變量.\n",
                      reclaim_objects()));
        return 1;
}

int help()
{
        write(@TEXT
指令格式: reclaim

查閲所有的對象，清除那些不應繼續保存在內存中的變量。
TEXT );
        return 1;
}