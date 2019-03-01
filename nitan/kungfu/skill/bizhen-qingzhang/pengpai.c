// This program is a part of NITAN MudLIB
// bizhen-qingzhang  碧針清掌 澎湃
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("can_perform/bizhen-qingzhang/pengpai", me) )
                return notify_fail("你還不會使用這一招！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須空手才能施展「澎湃」這一招！\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("「澎湃」只能對戰鬥中的對手使用。\n");
 
        if (me->query_skill("bizhen-qingzhang", 1) < 180)
                return notify_fail("你的碧針清掌還不夠嫻熟，還不能用掌力傷人！\n");

        if (me->query_skill_mapped("strike") != "bizhen-qingzhang")
                return notify_fail("你沒有激發碧針清掌，無法使用「澎湃」這一招！");

        if (me->query_skill("force") < 300)
                return notify_fail("你內功的修為不夠，無法用掌力傷人！\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，無法用掌力傷人！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠，無法用掌力傷人！\n");
 
       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲輕哼，雙掌揮舞出一個大圈，"
              "橫推而出，頓時一股洶湧澎湃的勁氣如波浪一般向$n"
              HIW "湧來。\n" NOR;
 
        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        me->start_busy(3);
        addn("neili", -200, me);

        if (ap / 2 + random(ap) < dp)
        {
                msg += HIY "只見$n" HIY "不慌不忙，輕輕一閃，躲過了$N" HIY "這一擊！\n"NOR;
        } else
        {
                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見$n" HIR "無法何擋這洶湧澎湃的氣流，噴出一大口鮮血，身子直線飛出！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}