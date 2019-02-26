// roar.c 鬼哭

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 10);

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能攻擊別人! \n");

        me->start_busy(5);
        message_combatd(HIR "$N" HIR "極嘶長呼，聲音淒厲之"
                        "極，令人毛骨悚然！\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;

                if( skill/2+random(skill/2)<query("con", ob[i])*2 )
                        continue;

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
                
                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "你只覺得耳膜欲破，心煩氣燥，噁心不止......\n");
                }
        }
        return 1;
}