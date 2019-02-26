// copyskill.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

protected int copy_stats(object me, object ob, string stats);
int help();

int main(object me, string arg)
{
        object ob;
        object tob;
        string stats, who, target;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
        {
                help();
                return 1;
        }

        if (sscanf(arg, "%s from %s to %s", stats, who, target) == 3)
        {
                if (! objectp(tob = present(target, environment(me))))
                        return notify_fail("你眼前沒有 " + target + " 這個物件。\n");
        } else
                tob = me;

        if (wiz_level(me) <= wiz_level(tob) && me != tob)
                return notify_fail("你只能給權限比自己低的人複製狀態。\n");

        if (who == "me")
                ob = me;
        else
        if (! objectp(ob = present(who, environment(me))))
                return notify_fail("你眼前沒有 " + who + " 這個物件。\n");

        if (! is_root(me) && playerp(tob) && ! wizardp(tob))
                return notify_fail("只有天神才能給普通玩家複製狀態。\n");

        if (ob == tob)
                return notify_fail("不需要複製吧。\n");

        if (me != tob)
                log_file("static/copystats", sprintf("%s %s copy %s(%s)'s stats to %s(%s).\n",
                                                     log_time(), log_id(me),
                                                     ob->name(1),query("id", ob),
                                                     tob->name(1), tob->query("id")));
        copy_stats(tob, ob, stats);
        message_vision(HIM + me->name(1) + HIM "口中唸唸有詞，只見一道紅光籠罩了$N"
                       HIM "和$n" HIM "。\n" NOR, tob, ob);
        return 1;
}

protected int copy_stats(object me, object ob, string stats)
{
        mapping your;
        mapping my;

        your = ob->query_entire_dbase();
        my = me->query_entire_dbase();
        
        if (! undefinedp(your[stats]))
                my[stats] = your[stats];
 
        return 1;
}

int help()
{
        write(@TEXT
指令格式：copystats <stats> from <對象> [to <目的對象>]

這個指令讓你複製對象的狀態。

該命令在可以被授權使用的信息包括：me、wizard、all。
TEXT );
        return 1 ;
}
