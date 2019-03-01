#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "奇劍訣" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me))
           || (string)query("skill_type", weapon) != "sword")
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xiaoyao-jian", 1) < 160)
                return notify_fail("你逍遙劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "xiaoyao-jian")
                return notify_fail("你沒有激發逍遙劍法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if (query("max_neili", me) < 2200)
                return notify_fail("你內力修為不足，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 350)
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIW "\n$N" HIW "將" + wn + HIW "斜指長空，猛地飛身躍起，"
              + wn + HIW "忽左忽右，飄忽不定，猛然間破空長響，" + wn + HIW
              "直指向$n" HIW "嚥喉。\n這正是逍遙劍法之「" HIG "奇劍訣" HIW "」，"
              "當真是招招精奇，神妙無比。" NOR;

        message_combatd(msg, me, target);

        ap = attack_power(me, "sword") + me->query_skill("dodge");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 78,
                                          HIR "$n" HIR "只見一道電光從半空襲來，"
                                          "心中驚駭不已，但鮮血已從$n胸口噴出。\n"
                                          NOR);
                me->start_busy(2 + random(4));
                addn("neili", -300, me);
        } else
        {
                msg = CYN "然而$n" CYN "眼明手快，側身一跳"
                      "躲過$N" CYN "這一劍。\n" NOR;

                me->start_busy(2);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
