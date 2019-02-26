#include <ansi.h>
#include <combat.h>

#define JING "「" HIM "驚虹一筆" NOR "」"

inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if( userp(me) && !query("can_perform/canghong-bifa/jing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(JING "只能對戰鬥中的對手使用。\n");

        weapon=query_temp("weapon", me);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，難以施展" JING "。\n");

        skill = me->query_skill("canghong-bifa", 1);

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功修為不夠，難以施展" JING "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" JING "。\n");

        if (skill < 100)
                return notify_fail("你蒼虹筆法修為有限，難以施展" JING "。\n");

        if (me->query_skill_mapped("dagger") != "canghong-bifa")
                return notify_fail("你沒有激發蒼虹筆法，難以施展" JING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIM "$N" HIM "手中" + weapon->name() + HIM "大開大合，宛若天馬行"
              "空，難測陰陽，化作一道道疾光射向$n" HIM "！\n" NOR;
 
        ap = me->query_skill("dagger");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = 100 + ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "頓時只聽得“噗嗤”一聲，$n" HIR
                                           "胸口被$N" HIR "一筆刺中，濺出一柱鮮血。\n" NOR);
                me->start_busy(1);
                if (ap / 3 + random(ap) > dp && ! target->is_busy())
                        target->start_busy(ap / 25 + 1);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的一一拆解，沒露半點"
                       "破綻！\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}