// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "橫掃千軍" NOR; }

string final(object me, object target, int ap, int dp);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("baisheng-daofa", 1) < 150)
                return notify_fail("你百勝刀法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "baisheng-daofa")
                return notify_fail("你沒有激發百勝刀法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "blade") + me->query_str()*10;
        if( query("character", me) == "光明磊落" || query("character", me) == "國土無雙" )
        {
                msg = HIR "$N" HIR "嗔目大喝，殺氣凜然而起，手持" + weapon->name() +
                      HIR "義無反顧的猛然橫掃$n" HIR "，全然不顧生死，浩氣悵然！\n" NOR;
                ap += ap * 1 / 4;
        } else
                msg = HIR "$N" HIR "狂提內勁，將全身力道灌注於" + weapon->name() +
                      HIR "之上疾斬劈出，“唰”的一聲掃向$n" HIR "而去！\n" NOR;

        dp = defense_power(target, "force")  + target->query_str()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -350, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, ap, dp :));
                me->start_busy(2);
        } else
        {
                msg += HIC "$n" HIC "奮力招架，硬生生的擋住了這令天地失色之必殺一擊！\n" NOR;
                addn("neili", -150, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int ap, int dp)
{
        object weapon;
        string msg;

        msg = HIR "$n" HIR "連忙抵擋，卻那裏招架得住，整個人"
              "被這一擊打得飛身而起，遠落平沙。";
        if (ap / 3 > dp)
        {
                msg += "就此斃命！\n" NOR;
                call_out("char_killed", 0, target, me);
        } else
        if( (ap/2>dp) && objectp(weapon=query_temp("weapon", target)) )
        {
                msg += "手中的" + weapon->name() + HIR "再也拿捏不住，應聲而出。\n" NOR;
                weapon->unequip();
                weapon->move(environment(me));
        } else
                msg += "\n" NOR;
        return msg;
}

void char_killed(object ob, object me)
{
        if (objectp(ob) && objectp(me) && me->is_fighting(ob) &&
            environment(ob) == environment(me))
                ob->die(me);
}