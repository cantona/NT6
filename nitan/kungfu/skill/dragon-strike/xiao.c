// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define XIAO "「" HIW "龍嘯九天" NOR "」"

int can_not_hubo() { return 1;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, count;
        int i, damage;

/*
        if( query("family/family_name", me) != "丐幫" )
                return notify_fail("你不是丐幫弟子，無法使用" XIAO "。\n");
*/

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用" XIAO "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAO "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(XIAO "只能空手使用。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 1000)
                return notify_fail("你降龍十八掌火候不夠，難以施展" XIAO "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你沒有激發降龍十八掌，難以施展" XIAO "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你沒有準備降龍十八掌，難以施展" XIAO "。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的內功修為不夠，難以施展" XIAO "。\n");

        if( query("max_neili", me)<30000 )
                return notify_fail("你的內力修為不夠，難以施展" XIAO "。\n");

        if( query("neili", me)<3000 )
                return notify_fail("你現在的真氣不足，難以施展" XIAO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if( objectp(weapon=query_temp("weapon", target)) )
        {
                msg = HIW "$N" HIW "暴喝一聲，全身內勁迸發，氣貫右臂奮力外扯，企圖將$n"
                      HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");

                if (ap / 2 + random(ap) > dp)
                {
                        addn("neili", -300, me);
                        msg += HIR "$n" HIR "只覺周圍氣流湧動，手中" + weapon->name() +
                               HIR "竟然拿捏不住，向$N" HIR "掌心脱手飛去。\n" NOR;

                        weapon->move(environment());
                } else
                {
                        addn("neili", -200, me);
                        msg += CYN "$n" CYN "只覺周圍氣流湧動，慌忙中連將手中" + weapon->name() +
                               CYN "揮舞得密不透風，使得$N" CYN "無從下手。\n" NOR;
                }
                message_combatd(msg, me, target);
        }

        msg = WHT "忽然$N" WHT "身形激進，施出降龍十八掌之「" HIW "震驚百里" NOR +
              WHT "」，全身真氣鼓動，雙掌如排山倒海般壓向$n" WHT "。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        damage *= 2;

        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100,
                                           HIR "$n" HIR "只覺一股罡風湧至，根本不"
                                           "及躲避，$N" HIR "雙掌正中前胸，鮮血如"
                                           "箭般噴出。\n" NOR);
                target->set_weak(5);
                addn("neili", -400, me);
        } else
        {
                msg += CYN "$n" CYN "眼見$N" CYN "來勢洶湧，絲毫不"
                       "敢小覷，急忙閃在了一旁。\n" NOR;
                addn("neili", -200, me);
        }

        message_combatd(msg, me, target);

        msg = HIY "緊跟着$N" HIY "施出降龍十八掌「" HIW "飛龍在天"
              HIY "」，雙掌翻滾，宛如一條神龍攀蜒於九天之上。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面對$N" HIR "這排山倒海般的攻"
                       "勢，完全無法抵擋，招架散亂，連連退後。\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "心底微微一驚，心知不妙，急忙"
                       "凝聚心神，竭盡所能化解$N" HIC "數道掌力。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);
        addn_temp("apply/unarmed_damage", count/3, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy())
                        target->start_busy(5);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn("neili", -300, me);
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/unarmed_damage", -count/3, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIW "$N" HIW "右掌斜揮，前招掌力未消，此招掌力又到，竟然又攻出一招「" HIR "亢龍有悔" HIW "」，掌夾風勢，勢如破竹，\n"
              HIW "便如一堵無形氣牆，向前疾衝而去。$n" HIW "只覺氣血翻湧，氣息沉濁。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage * 3;
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 280 + random(20),
                                          HIR "結果$p躲閃不及，$P掌勁頓時穿胸而"
                                          "過，頓時口中鮮血狂噴。\n" NOR);
        } else
        {
                msg += HIC "$p眼見來勢兇猛，身形疾退，瞬間"
                       "飄出三丈，脱出掌力之外。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_busy(3 + random(3));
        addn("neili", -400-random(600), me);
        return 1;
}

