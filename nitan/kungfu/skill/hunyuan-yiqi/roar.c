// roar.c 佛門獅子吼

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<600 )
                return notify_fail("你的內力不夠。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        if( userp(me) && me->query_condition("killer") > 20)
                return notify_fail("你感到一絲內疚，手突然軟了下來！\n");

        skill = me->query_skill("force");

        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(3);
        message_combatd(
                HIY "$N深深地吸一囗氣，真力迸發，發出一聲驚天動地的巨吼ⅵ\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;

                if (skill / 2 + random(skill / 2) < (int)ob[i]->query_con() * 2)
                        continue;

                if (userp(ob[i]) && !ob[i]->die_protect(me))
                        continue;

                if (! living(ob[i]) || wizardp(ob[i]) ||
                    (query("age", ob[i])<17 && userp(ob[i])) )
                        continue;

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);

                damage=skill-(query("max_neili", ob[i])/20);
                if (damage > 0)
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "你覺得眼前一陣金星亂冒，耳朵痛得像是要裂開一樣ⅵ\n");
                }
        }

        return 1;
}

