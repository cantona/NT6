// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "亢龍有悔" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你內力修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 240)
                return notify_fail("你降龍十八掌火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你沒有激發降龍十八掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你沒有準備降龍十八掌，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        // 第一掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);

        message_combatd(sort_msg(HIW "\n忽然間$N" HIW "身形激進，左手一劃，右手呼的一掌，便"
                     "向$n" HIW "擊去，正是降龍十八掌「" NOR + HIY "亢龍有悔" NOR
                     + HIW "」一招，力自掌生之際説到便到，以排山倒海之勢向$n" HIW
                     "狂湧而去，當真石破天驚，威力無比。\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 65,
                                          HIR "$p" HIR "一楞，只見$P" HIR "身形"
                                          "一閃，已晃至自己跟前，躲閃不及，被擊"
                                          "個正中。\n:內傷@?");

                message_combatd(msg, me, target);

        } else
        {
                msg = HIC "$p" HIC "氣貫雙臂，凝神應對，遊刃有餘，$P"
                      HIC "掌力如泥牛入海，盡數卸去。\n" NOR;
                message_combatd(msg, me, target);
        }

        // 第二掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;

        message_combatd(sort_msg(HIW "\n$N" HIW "一掌既出，身子已然搶到離$n" HIW "三四丈之外"
                     "，後掌推前掌，兩股掌力道合併，又是一招「" NOR + HIY "亢龍有"
                     "悔" NOR + HIW "」攻出，掌力猶如怒潮狂湧，勢不可當。霎時$n"
                     HIW "便覺氣息窒滯，立足不穩。\n" NOR), me, target);
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 65,
                                           HIR "只聽$p" HIR "一聲慘嚎，被$P" HIR
                                           "一掌擊中胸前，“喀嚓喀嚓”斷了幾根肋"
                                           "骨。\n:內傷@?");

                message_combatd(msg, me, target);
        } else
        {
                msg = HIC "$p" HIC "氣貫雙臂，凝神應對，遊刃有餘，$P"
                      HIC "掌力如泥牛入海，盡數卸去。\n" NOR;
                message_combatd(msg, me, target);
        }

        // 第三掌
        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        message_combatd(sort_msg(HIW "\n緊跟着$N" HIW "一聲暴喝，右掌斜斜揮出，前招掌力未消"
                     "，此招掌力又到，竟然又攻出一招「" NOR + HIY "亢龍有悔" NOR
                     + HIW "」，掌夾風勢，勢如破竹，便如一堵無形氣牆，向前疾衝而"
                     "去。$n" HIW "只覺氣血翻湧，氣息沉濁。\n" NOR), me, target);

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 75,
                                           HIR "結果$p" HIR "躲閃不及，$P" HIR
                                           "的掌勁頓時穿胸而過，“哇”的噴出一大"
                                           "口鮮血。\n:內傷@?");

                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                addn("neili", -400-random(600), me);
                return 1;
        } else
        {
                msg = HIC "$p" HIC "見這招來勢兇猛，身形疾退，瞬間飄出三"
                      "丈，脱出$P" HIC "掌力之外。\n" NOR;
                message_combatd(msg, me, target);
                me->start_busy(1 + random(3));
                addn("neili", -400-random(600), me);
                return 1;
        }
        message_combatd(msg, me, target);
        return 1;
}
