#include <ansi.h>
#include <combat.h>

#define ZHE "「" HIG "隻手遮天" NOR "」"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

string final(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl, p;

        if( userp(me) && !query("can_perform/xuanming-zhang/zhe", me) )
                return notify_fail("你還沒有經過人指點，不會使用"ZHE"。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHE "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHE "只能空手施展。\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("你的玄冥神功火候不夠，無法施展" ZHE "。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("你的玄冥神掌不夠熟練，無法施展" ZHE "。\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("你沒有激發玄冥神功為內功，無法施展" ZHE "。\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("你沒有準備玄冥神掌，無法施展" ZHE "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不足，無法施展" ZHE "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法施展" ZHE "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "\n$N" HIW "運起玄冥神功，全身浮現出一層紫氣，猛然間雙掌翻騰不息，施"
                  "展出絕招「" HIG "隻手遮天" HIW "」，攜帶着萬古至毒至寒之氣的掌勁"
                  "攻向$n" HIW "！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        me->start_busy(4);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -300, me);
     
                // 玄冥寒毒反噬
                if( query("max_neili", target)*3/5>query("max_neili", me) )
                {
                        message_sort(msg, me, target);
                        message_sort(HIM "$N" HIM "一掌打在$n" HIM "身上，猛然間氣血翻騰，一股陰寒之氣竟"
                                     "反噬回來，$N" HIM "抵禦不住，寒毒侵入體內。$N" HIM "悶哼一聲，一"
                                     "口淤血吐出，臉色頓時發紫。" NOR, me, target);

                        me->receive_wound("qi",query("jiali", me)+random(query("jiali", me)/2));

                        p=query("qi", me)*100/query("max_qi", me);
                        msg = "( $N" + eff_status_msg(p) + " )\n\n";
                        message_vision(msg, me, target);

                        me->affect_by("xuanming_poison",
                                      (["level":query("jiali", me)+random(query("jiali", me)),
                                         "id":query("id", me),
                                         "duration" : lvl / 40 + random(lvl / 20) ]));

                        return 1;
                        
                } 

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看見$N" HIY "來勢洶湧，急忙提氣躍開。\n" NOR;
                addn("neili", -180, me);
        }
        message_sort(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         (["level":query("jiali", me)*3,
                            "id":query("id", me),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "只見眼前紫影晃動，突然間胸口一震，已知大勢"
               "不妙，只感胸口處一股寒氣升起，盡損三焦六脈。\n" NOR;
}
