// sp.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        mapping site_privilege;
        string item, desc;
        string msg;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(boss)"))
                return notify_fail("只有管理員才能授權該站點的使用權限。\n");

        if (! arg)
        {
                site_privilege = SECURITY_D->query_site_privilege();
                map_delete(site_privilege, INTERMUD_MUD_NAME);
                if (sizeof(site_privilege) < 1)
                {
                        write("目前該站點沒有賦予任何使用權限。\n");
                        return 1;
                }

                msg = "目前該站點(" + INTERMUD_MUD_NAME + ")賦予的使用權限信息如下：\n";

                foreach (item in keys(site_privilege))
                        msg += sprintf("%s : %s\n", item, site_privilege[item]);

                me->start_more(msg);
                return 1;
        }

        if (! me->is_admin())
                return notify_fail("你不能修改這個站點的使用權限。\n");

        if (sscanf(arg, "%s %s", item, desc) != 2)
        {
                item = arg;
                desc = 0;
        }

        if (desc == "0" || desc == "clear")
                desc = 0;

        if (! SECURITY_D->set_site_privilege(item, desc))
                return notify_fail("無法設置 " + item +
                                   " 方面的權限信息為 " + desc + "。\n");
        else
        if (! desc)
                write("清除了 " + item + " 方面的權限信息。\n");
        else
                write("Ok.\n");

        SECURITY_D->save();
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: sp <class> <info>

授權給本地站點某些方面的使用權限。info 如果為空或是 clear 則
表示取消這類的使用權限。
HELP );
        return 1;
}