// This program is a part of NITAN MudLIB
// gua.c 明玉功「冰河倒掛」

#include <ansi.h>
#include <combat.h>

string name() { return HIM "冰河倒掛" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp, pp;

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對！\n");

        if ((int)me->query_skill("mingyu-gong", 1) < 300)
                return notify_fail("你明玉功修為不夠，無法施展" +name()+ "。\n");

        if ((int)me->query_skill("sword", 1) < 300)
                return notify_fail("你劍法修為不夠，無法施展" +name()+ "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，無法施展" +name()+ "！\n");

        if (me->query_skill_mapped("sword") != "mingyu-gong")
                return notify_fail("你沒有將明玉功運用於劍法，無法使用" +name()+ "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        addn("neili", -300, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "force");
        pp = defense_power(target, "parry");

        damage = damage_power(me, "sword");

        message_combatd(HIW "\n$N" HIW "嬌喝一聲，手中" + weapon->name() + HIW "隨即不停舞動，如巨浪般卷"
                        "出，\n正是明玉功絕技「" HIM "冰河倒掛" HIW "」，突然" + weapon->name() + HIW
                        "幻出的冰河激射出四路襲向$n，勢不可擋．\n" NOR, me, target);

        msg = HIM "$N" HIM "將內力全灌入劍身，呼的一劍，當頭直劈。\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "憑藉自身高強的內功，硬是盪開此招。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75 + random(10),
                                           HIR "$n" HIR "不知此招之強，招架之下竟被$N"
                                           HIR "這一劍震得口吐鮮血，連連倒退。\n" NOR);
        }
        msg += HIM "\n$N" HIM "圈轉" + weapon->name() + HIM "，劍勢靈動，招招直指要害，劍光如網，鋪天蓋地。\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "的身法卻比劍勢還快，從容的閃過劍招。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(10),
                                           HIR "此招來勢當真快極，$n" HIR "哪裏來得及閃"
                                           "避招架？只見$N" HIR "劍光閃過，$n"
                                           HIR "混身霎時鮮血淋漓！\n" NOR);
        }
        msg += HIM "\n$N" HIM "反手一劍，疾刺$p" HIM "後心，劍法之快，部位之準，令人防不勝防。\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "身在空中，不及變招，只能揮出一招，正擊中$N"
                       CYN "劍上，略一借力，飄然避去。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(20),
                                           HIR "$n" HIR "身在空中，哪裏來得及變招？只見$N"
                                           HIR "此劍掠過，$n" HIR "大聲慘呼，鮮血四下飛濺！\n" NOR);
        }
        msg += HIM "\n$N" HIM "谷催十成功力，分身化影，猶如數個$N一起分襲擊$n。\n" NOR;
        if (me->query_skill("martial-cognize", 1) * 2 / 3 + random(me->query_skill("martial-cognize", 1)) <
            target->query_skill("martial-cognize", 1))
                msg += CYN "$n" CYN "不愧武學精湛，立分虛實，$n"
                       CYN "全力攻向$N。\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                           HIR "$n" HIR "慌亂出招，卻都只擊到殘影，"
                                           HIR "身上也同時多處中招．\n" NOR);
        }
        me->start_busy(4);
        message_combatd(msg, me, target);
        return 1;
}

