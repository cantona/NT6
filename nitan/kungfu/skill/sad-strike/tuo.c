// This program is a part of NITAN MudLIB
// tuo.c
// 楊過決戰金輪法王時所施展的決定勝負的一招。

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "拖泥帶水" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int effqi, maxqi;
        string couple;
        object cob;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query("static/marry", me)>1 )
                return notify_fail("你感情早已不純，哪裡還能領略到那種黯然銷魂的感覺？\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，使不出" + name() + "。\n");

        if ((int)me->query_skill("sad-strike", 1) < 180)
                return notify_fail("你的黯然銷魂掌不夠熟練，不會使用" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("你沒有激發黯然銷魂掌，無法使用" + name() + "。\n");

        if( !stringp(couple=query("couple/couple_id", me)) )
                return notify_fail("你沒有妻子，體會不到這種萬念俱灰的感覺。\n");
        /*
        if (! objectp(cob = find_player(couple)))
                return notify_fail("老婆不在啊，苦悶向誰發？\n");
        */
        if( time()-query_temp("last_perform/sad-strike/tuo", me)<60 )
                return notify_fail("你剛剛施展完拖泥帶水，現在心情沒有那麼鬱悶了。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        effqi=query("eff_qi", me);
        maxqi=query("max_qi", me);

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        me->start_busy(2);

        if (effqi < maxqi / 3)
        {
                msg = HIR "$N" HIR "心下萬念俱灰，凄然向妻子"
                      HIR "望了一眼，暗道：“別了！你自己保重。”\n"
                      "當下失魂落魄，隨手一招，恰好使出了黯然銷魂掌中"
                      "的「拖泥帶水」。\n" NOR;
                ap += ap  / 5;
        } else
        {
                msg = HIM "只見$N" HIM "沒精打採的揮袖卷出，拍出一掌，正是"
                      "黯然銷魂掌中的「拖泥帶水」。\n"NOR;
        }
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "unarmed");
                damage+= query("jiali", me);
                addn("neili", -300, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "只聽$n" HIR "一聲悶哼，“噗”的一"
                                           "聲，這一掌正好擊在$p" HIR "肩頭。 \n"
                                           NOR);
                set_temp("last_perform/sad-strike/tuo", 1, me);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "可是$p" HIC "小心應付、奮力招架，擋開了這一招。\n"
                       NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}