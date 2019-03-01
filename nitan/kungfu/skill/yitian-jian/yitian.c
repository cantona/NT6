// yitian.c 倚天劍決

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "倚天劍訣"; }

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;

        i = me->query_skill("yitian-jian", 1) + me->query_skill("linji-zhuang", 1);
        time = 5;
        if( !target ) target = offensive_target(me);

        if( !me->is_fighting() )
                return notify_fail("「倚天劍決」只能在戰鬥中使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("「倚天劍決」必須用劍才能使用！\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("你沒有激發倚天劍法，怎麼使用「倚天劍決」啊？\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內功修為不夠！\n");
        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠！\n");

        if( (int)me->query_skill("yitian-jian",1) < 120 )
                return notify_fail("你的倚天劍法還不到家，無法使用「倚天劍決」！\n");

        if( !living(target) )
                return notify_fail("對方已經這樣了，不需要這麼費力吧？！\n");

        msg =HIY "$N" HIY "長嘯一聲：\n" HIR "武林至尊、寶刀屠龍。號令天下，莫敢不從。倚天不出，誰與爭鋒? \n"
             HIR "頓時風雲變色，" HIR "$N" HIR "手中舞出漫天劍光........ \n" NOR;

        message_combatd(msg, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i*2, me);
        {
                msg =  HIC "-----拔雲見日!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天劍決，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }

                if( !living(target) ) return 1;
                        msg =  BLU "-----星河在天!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天劍決，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIY "-----倚天不出!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天劍決，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIR "-----誰與爭鋒!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N暗念倚天劍決，身法陡然加快！\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIM "-----號令天下!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
        }
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/damage", -i*2, me);
        addn("neili", -200, me);
        msg =HIY "$N暗念倚天劍決，身法陡然加快！\n" NOR;
        message_combatd(msg, me);
        me->start_busy(1+random(2));
        return 1;
}
