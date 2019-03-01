#include <ansi.h>
#include <combat.h>

#define WAN "「" HIR "萬劍焚雲" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg, wn;
        object weapon;
        int ap, dp, damage;

        me = this_player();

        if( userp(me) && !query("can_perform/zhurong-jian/wan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" WAN "。\n");

        if ((int)me->query_skill("zhurong-jian", 1) < 160)
                return notify_fail("你祝融劍法不夠嫻熟，難以施展" WAN "。\n");

        if (me->query_skill_mapped("sword") != "zhurong-jian")
                return notify_fail("你沒有激發祝融劍法，難以施展" WAN "。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你的內功火候不夠，難以施展" WAN "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" WAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();
                            
        msg = HIM "\n$N" HIM "劍招突變，將真氣注入劍身，劍體頓時變得通紅，一式「"
              HIR "萬劍焚雲" HIM "」使出，霎時呼嘯聲大作，手中" + wn + HIM "化做"
              "千萬柄利刃，籠罩$n" HIM "周身。" NOR; 

        message_sort(msg, me, target);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                 damage = damage_power(me, "sword");

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                          (: final, me, target, damage :));
                me->start_busy(3);
                 addn("neili", -200, me);
        } else
        {
                 msg = CYN "$n" CYN "眼劍" +wn + CYN"已至，強自鎮定，"
                      "側身躲過，但對$N" CYN "這招仍是心有余悸。\n" NOR;

                       me->start_busy(4);
                 addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        int lvl, n;

        lvl = me->query_skill("zhurong-jian", 1);
        n = 1 + random(lvl / 20);

        target->affect_by("zhurong_jian",
                ([ "level"    : lvl + random(lvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ]));

        return  HIR "只見$N" HIR "這一招疾如電、猛如火，$n"
                HIR "心中驚疑不定，電光火石間，已被$N" HIR
                "劃中" + chinese_number(n) + "劍，劍傷處嗤"
                "嗤作響，鮮血從外衣滲出。\n" NOR;
}