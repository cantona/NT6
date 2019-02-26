// summon command.

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string str;
        int i;

        if (wiz_level(me) < 1 ||
            ! SECURITY_D->valid_grant(me, "(wizard)"))
                return "/cmds/usr/summon"->main(me, arg);;

        if (! arg)
                return notify_fail("指令格式: Summon <player id> | <object>\n");

        str = arg;
        ob = find_player(str);
        if (! ob) ob = MESSAGE_D->find_user(str);
        if (! ob) ob = find_living(str);
        if (objectp(ob) && ! me->visible(ob))
                ob = 0;
        if (! ob) ob = find_object(str);
        if (! ob)
        {
                str=resolve_path(query("cwd", me),str);
                if (! sscanf(str, "%*s.c")) str += ".c";
                ob = find_object(str);
        }
        if (! ob)
                return "/cmds/usr/summon"->main(me, arg);

        if (wiz_level(ob) > wiz_level(me))
                return notify_fail("找踢啊。\n");

        if (environment(ob) == environment(me))
                return notify_fail("咦... 不就在你面前嗎？\n");

        if (environment(ob) == me)
                return notify_fail("咦... 不就在你身上嗎？\n");

        if (! me->is_admin() && query("id", me)  != "luoyun")
        {
                switch (SECURITY_D->query_site_privilege("summon"))
                {
                case "all":
                        break;

                case "noneuser":
                        if (playerp(ob))
                                return notify_fail("你不能對玩家施展法力。\n");
                        break;

                case "user":
                        if (! playerp(ob))
                                return notify_fail("你只能對玩家施展法力。\n");
                        break;

                default:
                        return notify_fail("你不能使用該命令。\n");
                }
        }

        // moving
        tell_room(environment(ob), HIM "天空中伸出一隻大手把"+
                  query("name", ob)+HIM"抓了起來,然後不見了。\n"NOR,ob);
        tell_object(ob,"一隻手把你抓了起來, 你眼前一陣黑....\n");
        tell_object(me, HIM "你把" + ob->name() + HIM "抓到你的面前。\n" NOR);
        tell_object(ob, HIM ".... 醒來時發現是" + me->name() + HIM
                    "把你弄過來的。\n" NOR);
        tell_room(environment(me), HIM + ob->name() + HIM "突然出現" +
                  "在你眼前。\n" NOR, ({ me, ob }));

        ob->move(environment(me));

        // ok ..
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : summon <某人> | <物品>

此指令可讓你(你)將某人或物品抓到你面前。

該命令在可以被授權使用的信息包括：noneuser, user、all。
HELP );
        return 1;
}