// accede.c
// 系統任務 ultra_quest 的相關文件

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        mapping q;
        string type;

        while (arg)
        {
                // 沒有任務，則返回
                if( !query("ultraquest/quest/id", me) )
                        return notify_fail("剛才沒人向你尋求幫助。\n");

                // 查看當前 ultra_quest 特殊任務的狀態
                if( !stringp(type=query("ultraquest/quest/type", me) )
                   || (type != "mathematics"            // 比試演算
                   && type != "literate"                // 比試詩詞
                   && type != "chess"                   // 比試棋技
                   && type != "calligraphy"             // 幫忙書法
                   && type != "drawing"                 // 幫忙繪畫
                   && type != "medical"))               // 幫忙治病
                        return notify_fail("剛才沒人向你尋求幫助。\n");

                if (! objectp(ob = present(arg, environment(me))))
                        return notify_fail("這裏沒有這個人。\n");

                if( query_temp("need_accede/user", ob) != query("id", me) )
                        return notify_fail(CYN + ob->name() + CYN "瞪眼"
                                           "望着你道：你是誰？找我有什麼"
                                           "事？\n" NOR);

                if (ob == me)
                        return notify_fail("自己應酬自己？\n");

                if (me->is_fighting())
                        return notify_fail("你還是打完架再説吧。\n");

                if (me->is_busy())
                        return notify_fail("你還是有空了再説吧。\n");

                if( !query("can_speak", ob) )
                        return notify_fail("你大腦有水？\n");

                if (! living(ob))
                        return notify_fail("你還是等" + ob->name() +
                                           "醒了後再説吧。\n");

                if (ob->is_fighting())
                        return notify_fail("你還是等" + ob->name() +
                                           "打完架再説吧。\n");

                if (ob->is_busy())
                        return notify_fail("你還是等" + ob->name() +
                                           "忙完了再説吧。\n");

                notify_fail(CYN + ob->name() + CYN "瞪眼望着你道：你是誰"
                            "？找我有什麼事？\n" NOR);

                return ob->need_accede(me);
        }
        write("你打算應酬誰？\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：accede <某人>

這個指令可以讓你應酬某些人對你提出的要求。
HELP);
        return 1;
}
