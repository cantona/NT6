#include <ansi.h>
#include <combat.h>

string name() { return HIY "金鉤奪魄" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "jinwu-goufa")
                return notify_fail("你沒有激發金蜈鉤法，無法施展" + name() + "。\n");

        if ((int)me->query_skill("jinwu-goufa", 1) < 160)
                return notify_fail("你的金蜈鉤法還不夠嫻熟，無法施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "突然$N" HIY "一聲冷哼，手中" + weapon->name() +
              NOR + HIY "揮出，在空中劃出個美麗的弧線，直攻$n" HIY
              "的要穴！\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        //me->want_kill(target);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2 + random(2));
                addn("neili", -200, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "只見$N" HIR "這一擊來勢好快，寒光一"
                               "閃，正鉤中$n" HIR "的嚥喉，$n" HIR "一聲"
                               "慘叫，軟綿綿的癱了下去。\n" NOR "( $n" RED
                               "受傷過重，已經有如風中殘燭，隨時都可能斷"
                               "氣。" NOR ")\n";
                        damage = -1;
                } else
                if( objectp(weapon2=query_temp("weapon", target)) &&
                    me->query_skill("sword") > target->query_skill("parry"))
                {
                        // if(userp(me))
                        msg += HIR "只聽“嗤啦”一聲，$n" HIR "手腕被"
                              "鉤個正中，手中" + weapon2->name() + NOR
                              + HIR "再也捉拿不住，脫手而飛！\n" NOR;
                        //me->start_busy(2 + random(2));
                        if( !target->is_busy() )
                                target->start_busy(2);
                        weapon2->move(environment(target));
                } else
                {
                        damage = damage_power(me, "sword");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n" HIR "飛身躲閃，然而只聽“嗤啦”"
                               "一聲，$N" HIR "的" + weapon->name()+ NOR
                               + HIR "正鉤在$n" HIR + limb + "上，頓時鮮"
                               "血狂濺而出。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target,
                               WEAPON_ATTACK, damage, 40, pmsg);
                }
        } else
        {
                me->start_busy(4);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，避開了這一招。\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
