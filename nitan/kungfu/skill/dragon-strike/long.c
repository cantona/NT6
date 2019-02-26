#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "龍嘯九天" NOR "」"
#define HUIP "「" HIR "亢龍有悔" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i;
        object weapon;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用" HUI "。\n");

        if( query("family/family_name", me) != "丐幫" 
         && member_array("丐幫", query("reborn/fams", me)) == -1 ) 
                return notify_fail("你尚未轉世重生，無法使用" HUI "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(HUI "只能空手使用。\n");

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("你內功修為不夠，難以施展" HUI "。\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("你內力修為不夠，難以施展" HUI "。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 1000)
                return notify_fail("你降龍十八掌火候不夠，難以施展" HUI "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你沒有激發降龍十八掌，難以施展" HUI "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你沒有準備降龍十八掌，難以施展" HUI "。\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("你現在真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        message_combatd(sort_msg(HIG "\n$N" HIG "凝神聚氣，神態淡然，左手虛劃，右手迴轉，聚氣於胸前，猛地雙"
                         "手推出，剎那間，一招變為數招，同時使出，正是降龍十八掌「" HIR "龍嘯九天" HIG "」，"
                         "氣勢恢弘，勢不可擋 ……\n" NOR), me, target);

        // 第一掌
        ap = attack_power(me, "strike") + me->query_str() * 15;
        dp = defense_power(target, "dodge") + target->query_dex() * 15;
        ap *= 2;

        message_combatd(sort_msg(HIW "忽然$N" HIW "身形激進，左手一劃，右手呼的一掌"
                     "拍向$n" HIW "，力自掌生之際"
                     "説到便到，以排山倒海之勢向$n" HIW "狂湧而去，當真石"
                     "破天驚，威力無比。\n" NOR), me, target);

        damage = damage_power(me, "strike");
        damage+= query("jiali", me);
        if (ap * 3 / 5 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$P身形一閃，竟已晃至$p跟前，$p躲"
                                          "閃不及，頓被擊個正中。\n" NOR);
        } else
        {
                msg = HIC "卻見$p氣貫雙臂，凝神應對，$P掌"
                      "力如泥牛入海，盡數卸去。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第二掌
        ap = attack_power(me, "strike") + me->query_str() * 15;
        dp = defense_power(target, "parry") + target->query_int() * 15;
        ap *= 2;

        message_combatd(sort_msg(HIW "$N" HIW "一掌既出，身子已然搶到離$n" HIW "三"
                     "四丈之外，後掌推前掌兩股掌力道合併，掌力猶如怒潮狂"
                     "湧，勢不可當。霎時$p便覺氣息窒"
                     "滯，立足不穩。\n" NOR), me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$p一聲慘嚎，被$P這一掌擊中胸前，"
                                          "喀嚓喀嚓斷了幾根肋骨。\n" NOR);
        } else
        {
                msg = HIC "可是$p全力抵擋招架，竟似遊刃有"
                      "餘，將$P的掌力卸於無形。\n" NOR;
        }
        message_combatd(msg, me, target);

        // 第三掌
        ap = attack_power(me, "strike") + me->query_str() * 15 + me->query_skill("force");
        dp = defense_power(target, "force") + target->query_con() * 15;
        ap *= 2;

        message_combatd(sort_msg(HIW "緊跟着$N" HIW "右掌斜揮，前招掌力未消，此招掌"
                     "力又到，竟然又攻出一招，掌夾風勢，勢如破竹，"
                     "便如一堵無形氣牆，向前疾衝而去。$n" HIW "只覺氣血翻"
                     "湧，氣息沉濁。\n" NOR), me, target);

        if (ap *11 / 20 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "結果$p躲閃不及，$P掌勁頓時穿胸而"
                                          "過，頓時口中鮮血狂噴。\n" NOR);
        } else
        {
                msg = HIC "$p眼見來勢兇猛，身形疾退，瞬間"
                      "飄出三丈，脱出掌力之外。\n" NOR;
        }
        message_combatd(msg, me, target);

        message_combatd(sort_msg(HIY "$N" HIY "毫無停頓，雙掌翻滾，宛如一條神龍攀蜒於九天之上"
                        "。\n" NOR), me, target);

        me->add_temp("apply/attack", 100000);
        me->add_temp("apply/damage", 5000);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add_temp("apply/attack", -100000);
        me->add_temp("apply/damage", -5000);

        weapon = target->query_temp("weapon");
        if (objectp(weapon))
        {
                message_combatd(sort_msg(HIG "\n$N" HIG "暴喝一聲，全身內勁迸發，氣貫右臂奮力外扯，企圖將$n"
                                HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR), me, target);

                ap = attack_power(me, "strike") + me->query_str() * 20;
                dp = defense_power(target, "parry") + target->query_dex() * 20;
                ap = ap + ap / 2;

                if (ap / 3 + random(ap) > dp)
                {
                        me->add("neili", -300);
                        msg = HIR "$n" HIR "只覺周圍氣流湧動，手中" + weapon->name()
                               + HIR "竟然拿捏不住，向$N" HIR "掌心脱手飛去。\n" NOR;
                        weapon->move(me, 1);
                } else
                {
                        me->add("neili", -200);
                        msg = CYN "$n" CYN "只覺周圍氣流湧動，慌忙中連將手中"
                               + weapon->name() + CYN "揮舞得密不透風，使得$N"
                               CYN "無從下手。\n" NOR;
                }
                message_combatd(msg, me, target);
        }

        if (random(5) == 1)
        {
                message_combatd(HIG "$N" HIG "生平從未見過如此凌厲恢弘的招式，竟被弄得不知所措。\n" NOR,
                                target);
                if( !target->is_busy() )
                        target->start_busy(5 + random(6));
        }

        me->start_busy(3 + random(3));
        me->add("neili", -3000);
        return 1;
}
