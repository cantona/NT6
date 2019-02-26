// push.c 推人

#include <ansi.h>

mapping default_where = ([
        "n":        "north",
        "s":        "south",
        "e":        "east",
        "w":        "west",
        "nu":        "northup",
        "su":        "southup",
        "eu":        "eastup",
        "wu":        "westup",
        "nd":        "northdown",
        "sd":        "southdown",
        "ed":        "eastdown",
        "wd":        "westdown",
        "ne":        "northeast",
        "nw":        "northwest",
        "se":        "southeast",
        "sw":        "southwest",
        "u":        "up",
        "d":        "down",
]);

mapping default_dirs = ([
        "north":        "北邊",
        "south":        "南邊",
        "east":                "東邊",
        "west":                "西邊",
        "northup":        "北邊",
        "southup":        "南邊",
        "eastup":        "東邊",
        "westup":        "西邊",
        "northdown":        "北邊",
        "southdown":        "南邊",
        "eastdown":        "東邊",
        "westdown":        "西邊",
        "northeast":        "東北",
        "northwest":        "西北",
        "southeast":        "東南",
        "southwest":        "西南",
        "up":                "上面",
        "down":                "下面",
        "enter":        "裏面",
        "out":                "外面",
]);

mapping default_undirs = ([
        "south":        "北邊",
        "north":        "南邊",
        "west":                "東邊",
        "east":                "西邊",
        "southup":        "北邊",
        "northup":        "南邊",
        "westup":        "東邊",
        "eastup":        "西邊",
        "southdown":        "北邊",
        "northdown":        "南邊",
        "westdown":        "東邊",
        "eastdown":        "西邊",
        "southwest":        "東北",
        "southeast":        "西北",
        "northwest":        "東南",
        "northeast":        "西南",
        "down":                "上面",
        "up":                "下面",
        "out":                "裏面",
        "enter":        "外面",
]);

int main(object me, string arg)
{
        string who, where, dir, undir, where_temp;
        object env, env_to;
        mapping exits;
        object target;
        string msg;
        int wiz_push;

        if (! arg || sscanf(arg, "%s to %s", who, where_temp) != 2) 
                return notify_fail("指令格式：push <人物> to <方向>\n");

        env = environment(me);
        if( !env || query("no_fight", env) )
                return notify_fail("這裏不是你囂張的地方。\n");

        if (! objectp(target = present(who, env)))
                return notify_fail("你要推開誰？\n");

        if (! target->is_character())
                return notify_fail("看清楚一點，那並不是生物。\n");

        if (target->is_fighting())
                return notify_fail("人家現在正在打架呢，你想去找扁啊。\n");

        if( query("doing", target) )
                return notify_fail("人家現在正在冥神用功，不太好打擾別人吧。\n");

        if (! living(target))
                return notify_fail("這人現在沒有知覺，你還是扶着人家走吧。\n");

        if (! playerp(target))
                return notify_fail("你看了看這個人，沒敢動。\n");

        if (! undefinedp(default_where[where_temp]))
                where = default_where[where_temp];
        else
                where = where_temp;

        if( !mapp(exits=query("exits", env)) || undefinedp(exits[where]) )
                return notify_fail("沒有這個方向。\n");

        if (! objectp(env_to = find_object(exits[where])))
        {
                call_other(exits[where], "???");
                env_to = find_object(exits[where]);
        }

        wiz_push = wiz_level(me) >= wiz_level("(wizard)");

        if (! wiz_push)
        {
                if( query("qi", me)<150 )
                        return notify_fail("你氣力不佳，推不動別人。\n");
        
                if( query("neili", me)<100 )
                        return notify_fail("你內力不濟，推不動別人。\n");
        
                if (me->query_skill("force") < 100)
                        return notify_fail("你內功修為有限，沒有到達舉輕若重的地步。\n");
        }

        if (! undefinedp(default_dirs[where]))
                dir = default_dirs[where];
        else
                dir = where;

        if (! undefinedp(default_undirs[where]))
                undir = default_undirs[where];
        else
                undir = where;

        switch (random(3))
        {
        case 0:
                msg = "$N清咳一聲，喝道：“讓開了！”，順勢就把$n往" +
                      dir + "一擠。\n";
                break;

        case 1:
                msg = "$N皺了皺眉頭，惱道：“閃開！”，隨手把$n往" +
                      dir + "一推。\n";
                break;

        default:
                msg = "$N雙目一瞪，喝道：“還不快快給我閃開？”，説罷把$n往" +
                      dir + "推去。\n";
                break;
        }

        if (! wiz_push)
        {
                me->receive_damage("qi", 100);
                addn("neili", -50, me);
        }

        if (wiz_level(me) < wiz_level(target))
                msg += "$N用力推了推，只覺得好像撞到了一堵牆一樣。\n";
        else
        if (! wiz_push && target->query_skill("force") >= 150)
                msg += "$N默運內力，卻覺得$n內功根基頗為紮實，這一下竟然沒有撼動對方，不由得一愣。\n";
        else
        {
                if (! env->valid_leave(target, where))
                {
                        message_vision(msg, me, target);
                        write("過不去，你推不動人家。\n");
                        return 1;
                }

                if (! target || environment(target) != env)
                {
                        message_vision(msg, me, target);
                        write("奇怪了，人呢？\n");
                        return 1;
                }

                msg += "只見$N這一下把$n“嘟嚕嘟嚕”的推了開去。\n";
                message_vision(msg, me, target);
                target->move(env_to);
                message("vision", "只見" + target->name() + "跌跌撞撞的從" +
                                  undir + "晃了過來。\n", env_to, target);
                if (! target->is_busy())
                        target->stary_busy(5);
                return 1;
        }
        
        message_vision(msg, me, target);
        if (! me->is_busy())
                me->start_busy(1);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : push <人物> to <方向>

這個指令讓你把覺得妨礙你的人推開，當然，倘若人家內功紮實，
你這一下子多半奏不了效。
HELP );
        return 1;
}
