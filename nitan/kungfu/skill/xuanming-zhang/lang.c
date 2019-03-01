#include <ansi.h>
#include <combat.h>

#define LANG "「" HIM "驚濤駭浪" NOR "」"

inherit F_SSERVER;

string final1(object me, object target, int lvl);
string final2(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl, p;

        if( userp(me) && !query("can_perform/xuanming-zhang/lang", me) )
                return notify_fail("你還沒有經過人指點，不會使用"LANG "。\n"); 

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LANG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(LANG "只能空手施展。\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 220)
                return notify_fail("你的玄冥神功火候不夠，無法施展" LANG "。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 220)
                return notify_fail("你的玄冥神掌不夠熟練，無法施展" LANG "。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不足，無法施展" LANG "。\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("你沒有激發玄冥神功為內功，無法施展" LANG "。\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("你沒有準備玄冥神掌，無法施展" LANG "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真氣不夠，無法施展" LANG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "\n$N" HIW "默運玄冥神功，展出絕招「" HIM "驚濤駭浪" HIW "」，猛然間欺身"
              "向前，雙掌齊出，掌風陰寒無比，掌未到，風先至，瞬息間雙掌已拍向$n" HIW "！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        me->start_busy(4);

        // 第一掌

        msg += HIM "\n$N" HIM "右掌向內一轉，忽又向前，猛然間直襲$n" HIM "面門。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -200, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final1, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看見$N" HIY "來勢洶湧，急忙提氣躍開。\n" NOR;
                addn("neili", -180, me);
        }
        message_sort(msg, me, target);
         
        // 第二掌
        msg = HIM "\n$N" HIM "長舒一口氣，左掌緊跟而出，風到掌到，正拍向$n" HIM "胸口。\n" NOR;
        dp = defense_power(target, "parry") + target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                          (: final2, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看見$N" HIY "來勢洶湧，急忙提氣躍開。\n" NOR;
                addn("neili", -180, me);
        }
        message_sort(msg, me, target);

        return 1;
}

string final1(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         (["level":query("jiali", me)*3,
                            "id":query("id", me),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "正欲閃躲，卻見$N" HIR "突然繞到$p" HIR "身後，$n" HIR "心中一"
                   "驚，背後中掌，頓覺脊樑處一股寒氣升起，盡損三焦六脈。\n" NOR;

}

string final2(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         (["level":query("jiali", me)*3,
                            "id":query("id", me),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "但見$N" HIR "右掌已攻出，正欲反擊。突然間胸口一震，不禁暗暗"
               "叫苦，頓感胸口處一股寒氣升起，盡損三焦六脈。\n" NOR;

}
