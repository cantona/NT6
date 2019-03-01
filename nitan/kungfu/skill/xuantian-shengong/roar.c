// roar.c 五雷嘯

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<400 )
                return notify_fail("你的內力不夠。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裡不能攻擊他人。\n");

        skill = me->query_skill("force");

        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "深深地吸一囗氣，發出一"
                        "聲驚天動地的長嘯！\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]) || ob[i] == me)
                        continue;
                if( skill/2+random(skill/2)<query("con", ob[i])*2 )
                        continue;

                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                        ob[i]->receive_wound("jing", damage);
                        tell_object(ob[i], "你覺得眼前一陣金星亂冒，耳朵痛得像是要裂開一樣！\n");
                }

                me->want_kill(ob[i]);
                ob[i]->kill_ob(me);
        }

        return 1;
}