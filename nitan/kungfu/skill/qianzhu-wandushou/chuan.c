#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";
string final(object me, object target, int lvl);
string name() { return "萬毒穿心"; }

int perform(object me, object target)
{
        string msg;
        int lvl;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( userp(me) && !query("reborn/times", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( me->is_busy() )
                return notify_fail("你正忙著呢。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("「萬毒穿心」只能空手才能施展。\n");

        if (! me->is_fighting(target))
                return notify_fail("「萬毒穿心」只能對戰鬥中的對手使用。\n");

        if (! target || ! target->is_character())
                return notify_fail("你要對誰施展萬毒穿心？\n");

        if (! living(target))
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("wudu-qishu", 1 ) < 300)
                return notify_fail("你的五毒奇術火候不足以施展萬毒穿心。\n");

        if ((int)me->query_skill("wudu-jing", 1 ) < 300)
                return notify_fail("你的五毒阱火候不足以施展萬毒穿心。\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 800)
                return notify_fail("你的千蛛萬毒手修為不夠，現在還無法施展萬毒穿心。\n");

        if (me->query_skill_prepared("hand") != "qianzhu-wandushou")
                return notify_fail("你沒有準備千蛛萬毒手，無法施展萬毒穿心。\n");

        if( query("neili", me)<4000 )
                return notify_fail("你的真氣不夠，現在無法施展萬毒穿心。\n");

        msg = HIY "$N" HIY "雙手猛然翻轉向前，掌間隱現陣陣黑氣，兇險無比，掌風到處，數股"
              "黑氣噴射而出，直奔$n" HIY "胸口。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                damage *= 6;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 400,
                                           (: final, me, target, lvl :));

                addn("neili", -4000, me);
                me->start_busy(2 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "運足內力，以深厚的內功"
                       "化解了這一指的毒勁。\n" NOR;
                me->start_busy(4);
                addn("neili", -3000, me);
        }

        message_combatd(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}

string final(object me, object target, int lvl)
{
        if (! userp(target))
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 100,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));
        else
                target->affect_by("wandu_chuanxin",
                                    ([ "level" : lvl * 50,
                                       "id":query("id", me),
                                       "duration" : lvl / 10 + random(lvl / 10) ]));

        return HIR "$n" HIR "只覺得數股毒氣透心而過，說不出的難受。\n" NOR;
}
