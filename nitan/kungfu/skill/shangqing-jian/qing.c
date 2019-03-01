#include <ansi.h>
#include <combat.h>

string name() { return HIG "清流劍" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 220)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("shangqing-jian", 1) < 160)
                return notify_fail("你的上清劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "shangqing-jian")
                return notify_fail("你沒有激發上清劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wname = weapon->name();

        damage = damage_power(me, "sword");

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        msg = HIG "$N" HIG "施出上清劍法「清流劍」絕技，手中" + wname +
              HIG "隨即一顫，對準$n" HIG "連攻數劍，招式凌厲無比！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20,
                                           HIR "$p" HIR "奮力抵擋，卻哪裡招架得住，被$P"
                                           HIR "這一劍刺中要脈，鮮血四處飛濺！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "凝神聚氣，硬聲聲將$P"
                       CYN "這一劍架開，絲毫無損。\n" NOR;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        msg += "\n" HIG "卻見$N" HIG "跨步上前，手中" + wname +
               HIG "劍招陡變，又攻出一劍，劍尖頓閃出數道劍光，"
               "籠罩$n" HIG "全身！\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "只覺眼花繚亂，一時難以勘透其"
                                           "中奧妙，連中數劍，被削得血肉模糊！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "絲毫不為$P"
                       CYN "華麗的劍光所動，穩穩將這一劍架開。\n" NOR;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        msg += "\n" HIG "$N" HIG "隨即一聲大喝，身外化身，劍外化劍，手中"
               + wname + HIG "頓時漾起一道青芒，再次攻向$n" HIG "而去！\n"
               NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$p" HIR "運氣抵擋，可只覺一股無形劍氣"
                                           "透體而過，難受之極，噴出數口鮮血！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "一口氣自丹田運了上來，$P"
                CYN "附體劍芒雖然厲害，卻未能傷$p" CYN "分毫。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -300, me);
        message_combatd(msg, me, target);
        return 1;
}