// mkdir.c
// updated by doing

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string dir;
        string grant;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg) return help(me);

        dir=resolve_path(query("cwd", me),arg);
        if (! me->is_admin()) 
        {
                grant = SECURITY_D->query_site_privilege("edit");
                if( !grant && !sscanf(dir, "/u/%*s") )
                        return notify_fail("你只能在你自己的目錄下建子目錄。\n");
                        
                if( grant != "all" && !sscanf(dir, "/%s/%*s", grant) )
                        return notify_fail("你只能在你自己目錄下以及" + grant + "目錄下建子目錄。\n");
        }
        seteuid(geteuid(me));
        if (mkdir(dir))
                write("Ok.\n");
        else
                write("你沒有在這裏建子目錄的權利。\n");
        return 1;        
}

int help(object me)
{
        write(@HELP
指令格式 : mkdir <子目錄名>

建立一個子目錄。

see also: rm
HELP );
        return 1;
}
