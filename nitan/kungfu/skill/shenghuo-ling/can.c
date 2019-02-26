// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "殘血令" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count;
        int damage, skill, ap, dp;
        int l;
        int i;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target) target = offensive_target(me);

        skill = me->query_skill("shenghuo-ling", 1);

        if (! (me->is_fighting()))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! objectp(weapon = query_temp("weapon", me)) ||
            (string)query("skill_type", weapon) != "sword")
                return notify_fail("你使用的兵器不對，不能使用聖火令法之" +
                                   name() + "。\n");

        if (skill < 220)
                return notify_fail("你的聖火令法等級不夠, 不能使用聖火令"
                                   "法之" + name() + "。\n");

        if (me->query_skill("force") < 350)
                return notify_fail("你的內功火候不夠，不能使用聖火令法之" +
                                   name() + "。\n");

        if (query("max_neili", me) < 5000)
                return notify_fail("你的內力修為不足，不能使用聖火令法之" +
                                   name() + "。\n");

        if (query("neili", me) < 400)
                return notify_fail("你的內力不夠，不能使用聖火令法之" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "shenghuo-ling")
                return notify_fail("你沒有激發聖火令法，無法使用" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲長嘯，手中" + weapon->name() +
              HIR "一轉，招數頓時變得詭異無比，從意想不到的方"
              "位攻向$n" HIR "！\n" NOR;

        // 配合聖火令法本身具備的 max_hit帶來額外的傷害。
        // 原著中該令法乃很難看透的招數，所以出現增加攻
        // 擊的效率非常大。
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "完全無法看透$N" HIR "招中虛實，不由得心"
                       "生懼意，招式一滯，登時破綻百出。\n" NOR;
                count = ap / 6;
                addn_temp("shenghuo-ling/max_hit", 1, me);
        } else
        {
                msg += HIY "$n" HIY "見$N" HIY "來勢洶湧，心底一驚，打起精"
                       "神小心接招。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -300, me);
        addn_temp("apply/attack", count, me);

        l = skill / 50;
        if (l > 15) l = 15;
        for (i = 0; i < l; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        addn_temp("apply/attack", -count, me);
        delete_temp("shenghuo-ling/max_hit", me);
        me->start_busy(1 + random(4));
        return 1;
}