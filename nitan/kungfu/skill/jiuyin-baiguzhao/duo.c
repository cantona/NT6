// ziwu.c 九陰白骨爪 - 奪命連環爪

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "奪命連環爪" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用"+name()+"！\n");

        if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 140)
                return notify_fail("你的九陰白骨爪還不夠嫻熟，不能使用"+name()+"。\n");

        if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao")
                return notify_fail("你沒有準備九陰白骨爪，無法使用"+name()+"。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用奪命連環爪。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        switch(query("character", me) )
        {
        case "心狠手辣":
                msg = HIR "$N" HIR "桀桀怪笑，手指微微彎曲，倏的衝$n"
                      HIR "頭頂抓下。\n" NOR;
                break;

        case "陰險奸詐":
                msg = HIR "$N" HIR "冷笑數聲，手指微微彎曲成爪，飛向$n"
                      HIR "頭頂抓下。\n" NOR;
                break;

        case "光明磊落":
                msg = HIR "$N" HIR "揚聲吐氣，手指微微彎曲成爪，奮力向$n"
                      HIR "頭頂抓下。\n" NOR;
                break;

        default:
                msg = HIR "$N" HIR "手指微微彎曲成爪，渾不經意的向$n"
                      HIR "頭頂抓下。\n" NOR;
                break;
        }

        addn("neili", -100, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        damage = damage_power(me, "claw");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage,115,
                                           HIR "$p" HIR "急忙閃頭，然而$N" HIR
                                           "這招來得好快，正插中$p" HIR "肩頭，"
                                           "登時鮮血淋漓。\n" NOR);
        } else
        {
                addn("neili", -150, me);
                me->start_busy(3);
                msg += HIC "$p" HIC "暗叫不好，急忙閃頭，可是$N"
                       HIC "手臂咔咔作響，忽然暴長，迅論無比的抓向$p。\n" NOR;
                dp = defense_power(target, "dodge");

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                                   HIR "$n" HIR "哪裏料到$N" HIR
                                                   "竟有如此變招，不及躲閃，肩頭被$P"
                                                   HIR "抓了個鮮血淋漓。\n" NOR);
                } else
                        msg += CYN "$n" CYN "不及多想，急切間飄然而退，讓$P"
                               CYN "這一招無功而返。\n" NOR;
        }

        message_combatd(msg, me, target);
        return 1;
}
