#include <ansi.h>
#include <combat.h>

#define HENG "「" HIC "橫空出世" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if( userp(me) && !query("can_perform/yinyang-ren/heng", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HENG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade") )
                return notify_fail("你使用的武器不對，難以施展" HENG "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" HENG "。\n");

        if (me->query_skill("yinyang-ren", 1) < 180)
                return notify_fail("你的陰陽刃法修為不夠，難以施展" HENG "。\n");

        if ((int)me->query_skill("dodge") < 200)
                return notify_fail("你的輕功火候不夠，難以施展" HENG "。\n");  

        if( query("max_neili", me)<2700 )
                return notify_fail("你的內力修為不足，難以施展" HENG "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" HENG "。\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
            && me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("你沒有激發陰陽刃法，難以施展" HENG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "\n只見$N" HIY "手中" + weapon->name() + HIY "斜指"
              "蒼天，猛然間招式突變，" + weapon->name() + HIY "“呼"
              "呼”作響，一式「" HIC "橫空出世" HIY "」，力劈虛空，"
              "氣壓群山，猶如風卷殘雲般地襲向$n" HIY "。\n" NOR;
        message_sort(msg, me, target);

        // 根據所激發的是sword或blade來判斷ap值。
        if (me->query_skill_mapped("sword") == "yinyang-ren")
                ap = me->query_skill("sword");
        else 
                ap = me->query_skill("blade");

        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap);
                addn("neili", -240, me);
                me->start_busy(2 + random(2));
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "見此招來勢兇猛， 阻擋不"
                                           "及， 頓時被" + weapon->name() + HIR 
                                           "所傷，苦不堪言。\n" NOR);
        } else
        {
                addn("neili", -150, me);
                me->start_busy(1 + random(2));
                msg = CYN "可卻見" CYN "$n" CYN "猛的拔地而起，避開了"
                       CYN "$N" CYN "來勢兇猛的一招。\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}