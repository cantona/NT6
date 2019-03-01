// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "腐屍毒" NOR; }

inherit F_SSERVER;


string final(object me, object target, int damage);

int perform(object me, object target)
{
        object *corpse;
        int lvl, lvp, damage;
        int ap, dp;
        string name, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( userp(me) && (query_temp("weapon", me )
            || query_temp("secondary_weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        lvl = me->query_skill("chousui-zhang", 1);
        lvp = me->query_skill("poison");

        if (lvl < 140)
                return notify_fail("你的抽髓掌不夠嫻熟，難以施展" + name() + "。\n");

        if (lvp < 200)
                return notify_fail("你對毒技的了解不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("throwing") < 180)
                return notify_fail("你暗器手法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("你沒有激發抽髓掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你沒有準備抽髓掌，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的內息不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        /*
        corpse = filter_array(all_inventory(environment(me)),
                             (: base_name($1) == CORPSE_OB
                              && (query("defeated_by", $1) == this_player( )
                              || !query("defeated_by", $1)):));

        if (userp(me) && sizeof(corpse) < 1)
                return notify_fail("你附近沒有合適的屍體，難以施展" + name() + "。\n");

        // 允許等級 250 以上的任務 NPC 施展此招
        if (! userp(me) && lvl < 250 && sizeof(corpse) < 1)
                return notify_fail("你附近沒有合適的屍體，難以施展" + name() + "。\n");

        if (sizeof(corpse) >= 1)
                name = corpse[0]->name();
        else
        */
                name = "路邊的行人";

        msg = WHT "$N" WHT "隨手抓起" + name + WHT "，將「"
              HIR "腐屍毒" NOR + WHT"」毒質運于其上，朝$n"
              WHT "猛擲而去。\n" NOR;

        ap = attack_power(me, "strike") +
             me->query_skill("poison", 1);

        // 將任務NPC和玩家區分，再計算防御狀況
        if (userp(me))
                dp = defense_power(target, "dodge") +
                     target->query_skill("martial-cognize")/2;
        else
                dp = defense_power(target, "dodge") +
                     target->query_skill("parry", 1)/2;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "可是$n" CYN "見勢不妙，急忙騰挪身形，終"
                       "于避開了$N" CYN "擲來的屍體。\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        /*
        if (sizeof(corpse) >= 1)
                destruct(corpse[0]);
        */

        return 1;
}

string final(object me, object target, int damage)
{
        int lvp = me->query_skill("poison");

        target->affect_by("corpse_poison",
                ([ "level"    : lvp * 10 + random(lvp * 15),
                   "id":query("id", me),
                   "duration" : 20 + random(lvp / 20) ]));

        target->receive_damage("jing", damage, me);
        target->receive_wound("jing", damage / 2, me);

        return  HIR "$n" HIR "只聞一股惡臭傳來，大驚之下難以招"
                "架，頓被屍體擊個正中。\n" NOR;
}