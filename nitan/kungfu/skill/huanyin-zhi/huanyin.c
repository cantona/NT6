// huanyin.c 幻陰神指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp, damage;

        if (! target) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能攻擊別人! \n");

        if (! target || ! target->is_character())
                return notify_fail("施毒只能對對手使用。\n");

        if( query("not_living", target) )
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不足以施展幻陰神指。\n");

        if ((int)me->query_skill("huanyin-zhi", 1) < 150)
                return notify_fail("你的幻陰指法修為不夠，現在還無法施展幻陰神指。\n");

        if (me->query_skill_mapped("finger") != "huanyin-zhi")
                return notify_fail("你沒有激發幻陰指法，無法施展幻陰神指。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，現在無法施展幻陰神指。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "深深的吸了一口氣，緩緩的刺"
              "出一指，挾待一股寒氣逼向$n" HIG "。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIG "$p" HIG "急忙後退，然而這指何等玄妙，正"
                                           "好點中$p" HIG "胸前，$p" HIG "不禁打了一個冷"
                                           "戰。\n" NOR);
                target->affect_by("huanyin_poison",
                                  ([ "level" : ap / 5 + random(ap / 5),
                                     "id":query("id", me),
                                     "duration" : ap / 40 + random(ap / 18) ]));
                addn("neili", -320, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "運足內力，以深厚的內功"
                       "化解了這一指的陰寒內力。\n" NOR;
                me->start_busy(4);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}