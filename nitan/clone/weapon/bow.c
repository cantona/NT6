// bow.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("短弓", ({ "short bow", "bow", "duan gong", "gong" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", "一張短弓，打造得頗為精緻，具有不錯的準確度。\n");
                set("value", 20000);
                set("power", 100000);   // 攻擊威力
                set("accuracy", 120);   // 準確度120%
        }
        setup();
}

void init()
{
        if (this_player() == environment())
                add_action("do_shot", "shot");
}

int do_shot(string arg)
{
        string target, item;
        object me, victim;
        object ob;
        object env;
        int amount;
        int my_exp, v_exp;
        int ap;
        string msg;

        me = this_player();
        if( query_temp("handing", me) != this_object() )
                return notify_fail("你得先把" + name() + "拿(hand)在手中才行。\n");

        env = environment(me);
        if( !env || query("no_fight", env) )
                return notify_fail("這裏不能戰鬥。\n");

        if (me->is_busy())
                return notify_fail("你現在忙着呢。\n");

        if( query("jing", me)<80 )
                return notify_fail("你現在精神不夠好，無法使用" + name() +
                                   "攻擊對手。\n");

        if (userp(me))
        {
                if (! arg)
                        return notify_fail("你想攻擊誰？\n");

                if (sscanf(arg, "%s with %s", target, item) != 2)
                        return notify_fail("你要用什麼攻擊對手？(shot <對"
                                           "象> with <利器>)\n");

                if (! objectp(ob = present(item, me)))
                        return notify_fail("你身上沒有 " + item + " 這樣物"
                                           "品可以發射。\n");

                if (! ob->is_arrow())
                        return notify_fail("這不是箭，你無法發射。\n");

                if ((amount = ob->query_amount()) < 1)
                        return notify_fail("你身上的" + ob->name() + "不夠"
                                           "用了。\n");

                if (! objectp(victim = present(target, env)))
                        return notify_fail("這裏沒有這個人。\n");

                if( !victim->is_character() || query("not_living", victim) )
                        return notify_fail("看清楚了，那不是活人！\n");

                if (! me->is_fighting(victim))
                        return notify_fail("你只能射擊戰鬥中的對手。\n");
        } else
        {
                if (! objectp(ob = present("arrow", me))
                   || ! ob->is_arrow()
                   || (amount = ob->query_amount()) < 1)
                        return notify_fail("射擊失敗。\n");

                me->clean_up_enemy();
                victim = me->select_opponent();
        }

        if( query("special_skill/accuracy", me) )
                my_exp=query("combat_exp", me)*2;
        else
                my_exp=query("combat_exp", me);

        v_exp=query("combat_exp", victim);

        if (my_exp < 10000)
                return notify_fail("你實戰經驗太淺，難以運用" + name() + "射擊對手。\n");

        switch (random(3))
        {
        case 0:
                msg = HIY "$N" HIY "左手猛地抬起" + name() + HIY "，隨手抽出一"
                      +query("base_unit", ob)+ob->name()+HIY"，「嗖」的一"
                      "聲直射$n" HIY "而去！\n" NOR;
                break;

        case 1:
                msg = HIY "電光火石間$N" HIY "舉起" + name() + HIY "陡然射出一"
                      +query("base_unit", ob)+ob->name()+HIY"，帶着箭嘯直"
                      "奔$n" HIY "而去！\n" NOR;
                break;

        default:
                msg=HIY"霎時只聽「嗖」的一聲破空聲響，那"+query("base_unit", ob )
                      + ob->name() + HIY "已從$N" HIY "的" + name() + HIY "弦上"
                      "射出，飛貫向$n" HIY "！\n" NOR;
                break;
        }

        ap = my_exp * query("accuracy") / 100;
        if (userp(victim)) ap /= 2;

        if (v_exp / 2 + random(v_exp) > query("power") || ap < v_exp)
        {
                switch (random(3))
                {
                case 0:
                        msg += CYN "卻見$n" CYN "輕輕一閃，已將$N" CYN "射出"
                               "的箭避了開去。\n" NOR;
                        break;
                case 1:
                        msg += CYN "只見$n" CYN "不慌不忙，身子向一旁橫移數"
                               "尺，躲開了$N" CYN "這一招。\n" NOR;
                        break;
                default:
                        msg += CYN "可是$n" CYN "身子往後一仰，頓時讓$N" CYN
                               "射出的箭落空。\n";
                        break;
                }
        } else
        {
                msg += COMBAT_D->do_damage(me, victim, ob,
                                           query("weapon_prop/damage", ob),
                                           query("wound_percent", ob),
                                           HIR "只見$p" HIR "一個閃避不及，正中$P"
                                           HIR "這一" + ob->name() + HIR "，登時"
                                           "鮮血飛濺！\n" NOR);
        }
        ob->add_amount(-1);
        me->start_busy(2);
        me->receive_damage("jing", 10);

        message_combatd(msg, me, victim);
        return 1;
}