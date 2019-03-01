// This program is a part of NITAN MudLIB
// fumo.c 韋托伏魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "韋托伏魔"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「韋托伏魔」只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以使用這一絕技！\n");

        if (me->query_skill("weituo-gun", 1) < 135)
                return notify_fail("你的韋陀棍法修為不夠，目前不能使用韋托伏魔！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真氣不夠，不能使用韋托伏魔！\n");

        if (me->query_skill_mapped("club") != "weituo-gun")
                return notify_fail("你沒有激發韋陀棍法，不能使用韋托伏魔！\n");

        if( query("shen", me)<10000 )
                return notify_fail("你正氣不足，難以理解韋托伏魔的精髓。\n");

        msg = HIY "$N" HIY "臉色柔和，盡顯一派慈祥之意，手中的" + weapon->name() +
              HIY "輕旋，恍惚中顯出佛家韋陀神像，神光四射，籠罩住$n" + HIY "！\n" NOR;

        if (target->is_bad())
        {
                ap=query("shen", me)/1000;
                if (ap > 100) ap = (ap - 100) / 4 + 100;
                if (ap > 200) ap = (ap - 200) / 4 + 200;
                if (ap > 300) ap = (ap - 300) / 4 + 300;
                if (ap > 500) ap = 500;
                msg += HIR "$n" HIR "平日作惡不少，見了此情此景，心中不禁顫然！\n" NOR;
        } else
                ap = 0;

        ap += attack_power(me, "club");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "club");
                damage+= query("jiali", me);
                addn("neili", -500, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 150,
                                           HIR "結果只聽$p" HIR "一聲慘叫，被$P"
                                           "一下子打中要害，七竅一起生煙，耳鼻都滲出血來！\n" NOR);
                me->start_busy(1 + random(2));

        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "強攝心神，沒有被$P"
                       CYN "所迷惑，硬生生的架住了$P" CYN "這一招！\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}