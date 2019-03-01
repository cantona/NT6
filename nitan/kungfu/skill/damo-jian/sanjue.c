// This program is a part of NITAN MudLIB
// sanjue.c  達摩劍 達摩三絕劍

#include <ansi.h>

inherit F_SSERVER;
string name() { return "達摩三絕劍"; }

int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「達摩三絕劍」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_dex() < 30)
                return notify_fail("你的身法不夠，目前還不能使用這項絕技！\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");

        if (me->query_skill("dodge") < 200)
                return notify_fail("你的輕功修為不夠，不能使用達摩三絕劍！\n");

        if (me->query_skill("sword") < 200)
                return notify_fail("你的劍法修為不夠，目前不能使用達摩三絕劍！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，不能使用達摩三絕劍！\n");

        if (me->query_skill_mapped("sword") != "damo-jian")
                return notify_fail("你沒有激發達摩劍，不能使用達摩三絕劍！\n");

        msg = HIC "$N" HIC "使出達摩劍的絕技「達摩三絕劍」，身法陡然加快！\n" NOR;
        message_combatd(msg, me);

        addn("neili", -75, me);

        // The first attack
        addn_temp("apply/attack", 1000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // The second attack
        addn_temp("apply/attack", 2000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // The third attack
        addn_temp("apply/attack", 3000, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // Back
        addn_temp("apply/attack", -6000, me);

        me->start_busy(1 + random(2));

        return 1;
}
