// This program is a part of NITAN MudLIB
// zhua.c 神龍抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "神龍抓"; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「神龍抓」只能在戰鬥中對對手使用。\n");

        skill = me->query_skill("longzhua-gong", 1);

        if (skill < 135)
                return notify_fail("你的龍爪功等級不夠，不會使用「神龍抓」！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法運用「神龍抓」！\n");

        if (me->query_skill_mapped("claw") != "longzhua-gong")
                return notify_fail("你沒有激發龍爪功，無法使用「神龍抓」！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "大喝一聲，飛身撲至$n" HIY "面前，隨即伸手抓向"
              "$p" HIY "的要害！\n" NOR;

        ap = attack_power(me, "claw") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -180, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "見來勢兇猛，難以躲避，只好"
                                           "勉強化解，誰知$P" HIR "的手好像長了眼睛"
                                           "一般，撲哧一下正抓中$p" HIR "的要害，登"
                                           "時鮮血飛濺！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，連消帶打，全然化解了$P"
                       CYN "的攻勢。\n" NOR;
                addn("neili", -60, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
