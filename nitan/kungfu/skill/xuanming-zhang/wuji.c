#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("玄冥無極只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用玄冥無極。\n");         

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("你的玄冥神功火候不夠，使不出玄冥無極。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("你的玄冥神掌不夠熟練，不會使用玄冥無極。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不足，無法使用玄冥無極。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用玄冥無極。\n");

        msg = MAG "$N運起玄冥神功，全身浮現出一層紫氣，猛然間雙掌翻騰，施展出絕招玄冥\n無極，攜帶著萬古至毒至寒之氣的掌勁已攻向$n！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);
        ap=attack_power(me,"strike")+query("str", me)*10;
        dp=defense_power(target,"dodge")+query("dex", target)*10;
        me->start_busy(4);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -400, me);
                target->affect_by("xuanming_poison",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
               MAG "$n只見眼前紫影晃動，突然間胸口一震，已知大勢不妙，只感胸口處一股\n寒氣升起，盡損三焦六脈。\n" NOR);
        } else
        {
                msg += HIY "$n看見$N來勢洶湧，急忙提氣躍開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}