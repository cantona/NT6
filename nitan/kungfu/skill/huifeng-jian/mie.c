// mie.c  回風拂柳劍法「滅劍」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "滅劍" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，無法施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("你沒有激發回風拂柳劍法，無法施展" + name() + "。\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 120)
                return notify_fail("你的回風拂柳劍法不夠嫻熟，無法施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不夠，無法施展" + name() + "。\n");

        if( query("neili", me)<500 )
               return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "手中長劍劍芒躍動，劍光暴長，幻出死亡的色彩，劍尖漸"
              "漸逼近$n" HIR "，\n$n" HIR "看到漫天劍光，抽身後躍，可是只這一剎"
              "，$N" HIR "漫天劍影化為一劍直\n刺$n" HIR "前胸，快捷無倫，只有一"
              "劍！\n" NOR;


        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$n" HIR "全然無法躲避，" + weapon->name() +
                                           HIR "端端正正紮進在$p" HIR "的胸口，鮮血登時飛濺"
                                           "而出。\n" NOR);
                addn("neili", -150, me);
        } else
        {
                me->start_busy(3);
                msg += YEL "可是$p" YEL "輕輕一笑，側身右轉，伸"
                       "出兩指，正彈在$P" YEL "的劍上，" + weapon->name() +
                       YEL "在$p" YEL "身側劃過，有驚無險。\n"NOR;
                addn("neili", -60, me);
        }
        message_combatd(msg, me, target);
        return 1;
}
