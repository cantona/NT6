#include <ansi.h>
#include <combat.h>

#define HUAN "「" HIR "幻遁寒星" NOR "」"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/pidi-shenzhen/huan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿着暗器。\n");

        if (weapon->query_amount() < 20)
                return notify_fail("至少要有二十枚暗器才能施展" HUAN "。\n");

        if ((skill = me->query_skill("pidi-shenzhen", 1)) < 140)
                return notify_fail("你的闢地神針不夠嫻熟，難以施展" HUAN "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" HUAN "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" HUAN "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "只聽$N" HIR "一聲陰笑，身體急速旋轉，頓時將手中所有的"
              + weapon->name() + HIR "朝着四面八方打了出去！\n" NOR;

        my_exp=query("combat_exp", me)/100+skill*skill/1000*skill;
        ob_exp=(query("combat_exp", target)/100);

        if (random(my_exp) > ob_exp)
        {
                n = 4 + random(4);
                if (random(my_exp) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 2) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 4) > ob_exp) n += 4 + random(8);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += HIR "$n" HIR "霎時只見無數寒芒暴雨般向自己襲來，躲"
                       "閃不及，接連中了$P" HIR + chinese_number(n) +
                       query("base_unit", weapon)+weapon->name()+HIR
                       "。\n" NOR;
                target->receive_damage("qi", skill + random(skill), me);
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*15);
                }

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;

                msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$p" CYN "見得$P" CYN "招數奇特，不敢大意，當"
                       "即飛身躲開了所有" + weapon->name() + CYN "。\n" NOR;
                message_combatd(msg, me, target);
        }

        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}