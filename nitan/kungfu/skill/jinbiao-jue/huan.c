#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIY "金蓮幻生" NOR "」"

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/jinbiao-jue/huan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中沒有拿著暗器，難以施展" HUAN "。\n");

        if ((skill = me->query_skill("jinbiao-jue", 1)) < 100)
                return notify_fail("你的金鏢訣不夠嫻熟，難以施展" HUAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" HUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg= HIY "忽然間只見$N" HIY "單袖一揚，袖底頓時竄起一道金光，徑直向$n"
             HIY "電射而去。\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                msg += HIR "結果$p" HIR "躲閃不及，被$P" + HIR "那" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "射中身體，頓時鮮血四處飛濺！\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "絲毫不亂，身子略傾，閃開了$P"
                       CYN "發出的" + weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}