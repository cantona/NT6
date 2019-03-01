// enforce.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int pts;
        int max;

        if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) )
                return notify_fail("指令格式：enforce|jiali <使出幾成內力傷敵>|none|max\n");

        if( !me->query_skill_mapped("force") )
                return notify_fail("你必須先 enable 一種內功。\n");

        max = (int)me->query_skill("force") / 2;
        // 狂暴之力增加加力上限 
        if (query("special_skill/might", me)) 
                max += max * 20 / 100;

        if( query("jingmai/jiali", me) )
                max+=query("jingmai/jiali", me);

        if( query("jingmai/finish", me) )
                max += ZHOUTIAN_D->query_jingmai_effect("jiali");

        if( arg=="none" )
                delete("jiali", me);
        else
        if( arg=="max" )
                set("jiali", max, me);
        else {
                if( pts < 0 || pts > max )
                        return notify_fail("你只能用 none 表示不運內力，或數字表示每一擊用幾點內力。\n");
                set("jiali", pts, me);
        }

        write("Ok.\n");
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: enforce|jiali <使出幾點內力傷敵>|none|max

這個指令讓你指定每次擊中敵人時，要發出幾點內力傷敵。

enforce none 則表示你不使用內力。
enforce max 則表示你使用最大內力。

See Also: enable
HELP );
        return 1;
}
