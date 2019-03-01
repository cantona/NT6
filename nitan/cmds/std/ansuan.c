// ansuan.c 暗算
// by King 97.05

#include <ansi.h>

mapping default_where = ([
        "n":    "north",
        "s":    "south",
        "e":    "east",
        "w":    "west",
        "nu":   "northup",
        "su":   "southup",
        "eu":   "eastup",
        "wu":   "westup",
        "nd":   "northdown",
        "sd":   "southdown",
        "ed":   "eastdown",
        "wd":   "westdown",
        "ne":   "northeast",
        "nw":   "northwest",
        "se":   "southeast",
        "sw":   "southwest",
        "u":    "up",
        "d":    "down",
]);

mapping default_dirs = ([
        "north":        "北邊",
        "south":        "南邊",
        "east":         "東邊",
        "west":         "西邊",
        "northup":      "北邊",
        "southup":      "南邊",
        "eastup":       "東邊",
        "westup":       "西邊",
        "northdown":    "北邊",
        "southdown":    "南邊",
        "eastdown":     "東邊",
        "westdown":     "西邊",
        "northeast":    "東北",
        "northwest":    "西北",
        "southeast":    "東南",
        "southwest":    "西南",
        "up":           "上面",
        "down":         "下面",
        "enter":        "裡面",
        "out":          "外面",
]);

mapping default_undirs = ([
        "south":        "北邊",
        "north":        "南邊",
        "west":         "東邊",
        "east":         "西邊",
        "southup":      "北邊",
        "northup":      "南邊",
        "westup":       "東邊",
        "eastup":       "西邊",
        "southdown":    "北邊",
        "northdown":    "南邊",
        "westdown":     "東邊",
        "eastdown":     "西邊",
        "southwest":    "東北",
        "southeast":    "西北",
        "northwest":    "東南",
        "northeast":    "西南",
        "down":         "上面",
        "up":           "下面",
        "out":          "裡面",
        "enter":        "外面",
]);

int main(object me, string arg)
{
        string who, where, dir, undir, where_temp;
        object env, old_env;
        mapping exits;
        object target;
        int count;
        string gen;

        if (me->is_chatter())
                return 0;

        if (! arg || sscanf(arg, "%s at %s", who, where_temp) != 2)
                return notify_fail("指令格式：ansuan <人物> at <方向>\n");

        env = environment(me);
        old_env = env;

        if (! undefinedp(default_where[where_temp]))
                where = default_where[where_temp];
        else
                where = where_temp;

        if( !mapp(exits=query("exits", env)) || undefinedp(exits[where]) )
                return notify_fail("沒有這個方向。\n");

        if (! objectp(env = find_object(exits[where])))
        {
                call_other(exits[where], "???");
                env = find_object(exits[where]);
        }

        if( query("no_fight", env) )
                return notify_fail("那裡禁止戰鬥。\n");

        if (! objectp(target = present(who, env)))
                return notify_fail("這個方向沒有此人。\n");

        if (! target->is_character())
                return notify_fail("看清楚一點，那並不是生物。\n");

        if (target->query_competitor())
                return notify_fail("人家正在和別人比武，你要是暗算人家"
                                   "也未免太無恥了吧？\n");

        if( me->is_busy() || query("doing", me) )
                return notify_fail("你的動作還沒有完成，不能暗算別人。\n");

        if (me->is_fighting())
                return notify_fail("你正忙著戰鬥呢，還有心思暗算別人？\n");

        if( !query("can_speak", target) )
                return notify_fail("你這人真有意思，連" + target->name() +
                                   "也想暗算。\n");

        if (! living(target))
                return notify_fail(target->name() + "都已經這樣了，你還用得著暗算嗎？\n");

        if( query("jing", me)<100 )
                return notify_fail("你無法集中精力，暗算不了別人。\n");

        if( query_temp("guarded", target) )
                return notify_fail(target->name() + "附近有幫手，不方便下手暗算。\n");

        notify_fail("你無法過去暗算別人。\n");
        if (! (int)old_env->valid_leave(me, where))
                return 0;

        if (environment(me) != old_env)
        {
                write("你昏了頭，不知道走到了什麼地方。\n");
                return 1;
        }

        notify_fail("你沒有辦法暗算人家。\n");
        if (! target->accept_ansuan(me))
                return 0;

        if (! undefinedp(default_dirs[where]))
                dir = default_dirs[where];
        else
                dir = where;

        if (! undefinedp(default_undirs[where]))
                undir = default_undirs[where];
        else
                undir = where;

        me->want_kill(target);
        if( query("gender", me) == "女性" )
                gen = "倩影";
        else
                gen = "人影";

        write( CYN"你摒息靜氣，縱身而起，向" + dir + "的" + target->name() + "撲去！\n"NOR);
        message("vision", CYN"\n一條" + gen + "忽然向" + dir + "撲去，轉眼間又回到原處！\n\n"NOR, environment(me), me);
        tell_object(target, CYN"\n一條" + gen + "忽然從" + undir + "向你撲來！\n\n"NOR);
        message("vision", CYN"\n一條" + gen + "忽然從" + undir + "向" + target->name() + "撲來！\n\n"NOR, environment(target), target);

        count = me->query_str();

        set_temp("apply/name", ({gen}), me);
        set_temp("apply/id", ({"none"}), me);
        set_temp("apply/short", ({gen}), me);
        set_temp("apply/long", ({gen}), me);

        me->move(environment(target));

        addn_temp("str", count, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 && 
            ! target->is_guarder())
        {
                message_vision(CYN"$N一時沒有防范，被$n攻了個措手不及！\n" NOR, target, me);
                if (! target->is_busy())
                        target->start_busy(random(4) + 2);
        } else
        {
                message_vision(CYN "$N經驗豐富，不及細看，立刻向$n反擊！\n" NOR, target, me);
                COMBAT_D->do_attack(target,me,query_temp("weapon", target));
        }

        addn_temp("str", -count, me);

        if( random(query("combat_exp", me))<query("combat_exp", target)/5 || 
            target->is_guarder())
        {
                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);

                tell_object(target, CYN "你一定神，原來是" + me->name() +
                                    "在暗算我！\n" NOR);
                write(CYN "不好，被" + target->name() + "發覺了！\n" NOR);
                message_vision(CYN "$N喝道：$n！你敢暗算我，我跟你沒完！\n"
                               NOR, target, me);
                if (! target->is_killing(me))
                        target->kill_ob(me);
                else
                        target->fight_ob(me);
                me->start_busy(3);
        } else
        {
                message("vision", CYN "\n" + gen + "轉瞬不見！\n\n" NOR,
                                  environment(target), me);
                tell_object(me, CYN"\n你立刻退回原處！\n\n"NOR);

                me->move(old_env);

                delete_temp("apply/name", me);
                delete_temp("apply/id", me);
                delete_temp("apply/short", me);
                delete_temp("apply/long", me);

                tell_object(target, CYN "你一定神，可是什麼都沒看見。\n" NOR);
                message("vision", CYN + target->name() + "一臉惶恐，竟"
                                  "不知道誰在暗算他！\n" NOR,
                                  environment(target), target);
                write(CYN "哈哈，" + target->name() + "居然沒看出來。\n" NOR);
                write(CYN "你搓了搓手，一臉無辜的樣子。\n" NOR);
        }

        if (! me->is_busy())
                me->start_busy(3);

        me->receive_damage("jing", 50);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : ansuan <人物> at <方向>

這個指令讓你暗算位于<方向>的<人物>。
如果暗算成功，則敵人發現不了你。否則...:)
HELP );
        return 1;
}
