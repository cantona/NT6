#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "蛛蠱決"; }

int perform(object me, object target)
{
        string msg;
        int lvl;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("這裏不能攻擊別人！\n");

        if (! target || ! target->is_character())
                return notify_fail("你要對誰施展蛛蠱決？\n");

        if( query("not_living", target) )
                return notify_fail("看清楚，那不是活人。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不足以施展蛛蠱決。\n");

        if ((int)me->query_skill("qianzhu-wandushou", 1) < 130)
                return notify_fail("你的千蛛萬毒手修為不夠，現在還無法施展蛛蠱決。\n");

        if (me->query_skill_mapped("hand") != "qianzhu-wandushou")
                return notify_fail("你沒有激發千蛛萬毒手，無法施展蛛蠱決。\n");

        if( query("neili", me)<400 )
                return notify_fail("你的真氣不夠，現在無法施展蛛蠱決。\n");

        msg = HIB "$N" HIB "施出蛛蠱決，只見一縷黑氣從"
              "指尖透出，只一閃就沒入了$n" HIB "的眉心！\n" NOR;

        ap = attack_power(me,"hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$p" HIR "只覺得一股如山的勁力順指尖猛"
                                           "攻過來，只覺得全身毒氣狂竄，“哇”的一聲"
                                           "吐出一口黑血！\n" NOR);
                target->affect_by("qianzhu_wandushou",
                                  ([ "level" : lvl / 2 + random(lvl / 2),
                                     "id":query("id", me),
                                     "duration" : lvl / 40 + random(lvl / 18) ]));
                addn("neili", -320, me);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "運足內力，以深厚的內功"
                       "化解了這一指的毒勁。\n" NOR;
                me->start_busy(3);
                addn("neili", -80, me);
        }
        message_combatd(msg, me, target);
        /*
        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);
        */
        return 1;
}