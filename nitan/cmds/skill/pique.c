// pique.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int pts, max_pts;

        pts = 0;
        if (! arg || (arg != "none" && ! sscanf(arg, "%d", pts)))
                return notify_fail("指令格式：pique|jianu <使出幾成憤怒傷敵>|none\n");

        max_pts = me->query_max_craze() / 100;
        if (max_pts < 1)
                return notify_fail("你的性格不合，無法使用憤怒攻擊。\n");

        if (pts > max_pts)
                return notify_fail("你每次出招只能使出 " + max_pts +
                                   " 點憤怒。\n");
        if (pts == 0)
                delete("jianu", me);
        else
                set("jianu", pts, me);

        write("Ok.\n");
        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: pique|jianu <使出幾點憤怒傷敵>|none
 
這個指令讓你指定每次擊中敵人時，要發出幾點憤怒以傷害對方。如
果使用了憤怒傷敵，則在攻擊中還有一定的機率可以使出憤怒必殺技
暴怒招式。

pique none 則表示你不使用憤怒。

HELP );
        return 1;
}