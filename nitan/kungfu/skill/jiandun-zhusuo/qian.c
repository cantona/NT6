#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "千頭萬緒" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if( userp(me) && !query("can_perform/jiandun-zhusuo/qian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對，難以施展" QIAN "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功的修為不夠，難以施展" QIAN "。\n");

        if (me->query_skill("jiandun-zhusuo", 1) < 120)
                return notify_fail("你的劍盾珠索修為不夠，難以施展" QIAN "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" QIAN "。\n");

        if (me->query_skill_mapped("whip") != "jiandun-zhusuo")
                return notify_fail("你沒有激發劍盾珠索，難以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wname = weapon->name();

        damage = me->query_skill("jiandun-zhusuo", 1) / 4;
        damage += random(damage / 4);

        ap = me->query_skill("whip");
        dp = target->query_skill("parry");

        msg = HIW "$N" HIW "一聲輕哼，右手橫揮，手中" + wname +
              HIW "一招「千頭萬緒」對準$n" HIW "亂點下來。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           HIR "$p" HIR "抽身回退，卻已然不及，被"
                                           "$P" HIR "這招點中要穴，頓時口噴鮮血！\n"
                                           NOR);
        } else
        {
                msg += CYN "$p" CYN "凝神聚氣，硬聲聲將$P"
                       CYN "這一鞭架開，絲毫無損。\n" NOR;
        }

        ap = me->query_skill("whip");
        dp = target->query_skill("dodge");

        msg += "\n" HIW "卻見$N" HIW "跨步上前，手中" + wname +
               HIW "招數一變，反轉鞭鞘，抽向$n" HIW "而去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           HIR "便在$p" HIR "微微一楞間，已被$P"
                                           HIR "這招抽中，鮮血四處飛濺！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "急忙猛吸一口氣，飛"
                       "身躍起，躲開了這一招。\n" NOR;
        }

        ap = me->query_skill("whip");
        dp = target->query_skill("force");

        msg += "\n" HIW "緊接著又見$N" HIW "縱身而起，單手將" + wname +
               HIW "急速舞動，凌空朝著$n" HIW "圈去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 10,
                                           HIR "頓時便聽“啪”的一聲悶響，$n" HIR
                                           "竟被" + wname + HIR "卷至半空，重重"
                                           "摔下，再也無力爬起！\n" NOR);
        } else
        {
                msg += CYN "可$p" CYN "一個翻滾，起身時已在"
                       "丈許開外，便將這式化解于無形。\n" NOR;
        }
        me->start_busy(3 + random(3));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}