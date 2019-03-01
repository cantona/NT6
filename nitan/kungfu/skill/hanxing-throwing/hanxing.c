#include <ansi.h>
#include <combat.h>

#define HANXING "「" HIY "寒星八打" NOR "」"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/hanxing-throwing/hanxing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HANXING "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中沒有拿著暗器，難以施展" HANXING "。\n");

        if (weapon->query_amount() < 8)
                return notify_fail("至少要有三枚暗器才能施展" HANXING "。\n");

        if ((skill = me->query_skill("hanxing-bada", 1)) < 100)
                return notify_fail("你的寒星八打不夠嫻熟，難以施展" HANXING "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" HANXING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -80, me);
        weapon->add_amount(-3);

        msg= HIY "$N" HIY "突然縱身向後一個翻滾，就在快落地的一瞬"
             "間，$n" HIY "陡然發現幾點寒光閃爍不定地襲向自己！\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                msg += HIR "結果$p" HIR "反應不及，中了$P" + HIR "一" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "！\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+120);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "可是$p" HIG "從容不迫，輕巧的閃過了$P" HIG "發出的" +
                       weapon->name() + HIG "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}