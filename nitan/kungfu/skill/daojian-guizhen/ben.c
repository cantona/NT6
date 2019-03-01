#include <combat.h>
#include  <ansi.h>

string name() { return HIM "萬馬奔騰" NOR; }

string final1(object me, object target, int damage);

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, type1, type2;
        int ap, dp, lvl;
        object weapon1, weapon2;
        int attack_type;
        mapping prepare;
        int i;
        string* key_pre;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)query("max_neili", me) < 100000)
                return notify_fail("你內力修為不夠，難以施展" + name() + "。\n");

        if ((lvl = me->query_skill("daojian-guizhen", 1)) < 200)
                return notify_fail("你刀劍歸真修為不足200級，無法施展" + name() + "。\n");

        weapon1 = query_temp("weapon", me);
        weapon2 = query_temp("secondary_weapon", me) || query_temp("handing", me);

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("你沒有同時裝備刀劍，難以施展" + name() + "。\n");

        if (query("consistence", weapon2) <= 0)
                return notify_fail("你的" + weapon2->name() + "已經嚴重"
                                   "損壞，無法繼續使用了。\n");

        type1 = query("skill_type", weapon1);
        type2 = query("skill_type", weapon2);

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("你沒有同時裝備刀劍，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "daojian-guizhen"
           || me->query_skill_mapped("blade") != "daojian-guizhen")
                return notify_fail("你沒有激發刀劍歸真，難以施展" + name() + "。\n");

        if (query("neili", me) < 30000)
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -30000, me);

        ap = attack_power(me, "blade") +
             me->query_skill("sword", 1) + me->query_skill("blade", 1);
        dp = defense_power(target, "parry") + target->query_skill("sword", 1) +
             target->query_skill("blade", 1);

        message_combatd(HIY "$N" HIY "雙目微閉，衣裳無風自起，剎那間，殺氣充斥 ……\n"
                     HIC "一束刀光，" HIM "一道劍影，" HIY "一招「萬馬奔騰」毫無征兆地使出，刀光劍氣就猶如地\n"
                     "獄幽靈般地呼嘯而出，將$n" HIY "籠罩……\n" NOR, me, target);

        if (ap / 2 + random(ap / 2) > dp)
        {
                damage = damage_power(me, "blade");
                damage += damage_power(me, "sword");
                damage+=query("jiali", me);

                message_combatd(HIC "$N" HIC "被兩道飛馳而來的強光籠罩著，毫無思考的余地，只得拼死抵抗……\n" NOR, target);

                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 500 + 200 * (userp(me)?0:1),
                                          (: final1, me, target, damage :));
                message_combatd(msg, me, target);
        }
        else
        {
                message_combatd(HIM "$N" HIM "驚駭不已，卻硬著頭皮施展輕功閃避，竟無意間躲過此招。\n" NOR, target);
        }

        // 20%幾率無BUSY
        if (random(5) < 4) me->start_busy(3);
        target->start_busy(3);

        return 1;
}

string final1(object me, object target, int damage)
{
       if (! query_temp("daojian_cimu", target))
       {
               set_temp("block_msg/all", 1, target);
               target->apply_condition("no_perform", 5);
               set_temp("daojian_cimu", 1, target);
               call_out("cimu_end", 20 + random(31), me, target);
               return HIR "$n" HIR "只覺雙目被一陣強光略過，眼前一黑，就什麼"
                       "也看不見了，心中無限恐懼。\n" NOR;
        }
        else
                return "";
}

void cimu_end(object me, object target)
{
        if (target && query_temp("daojian_cimu", target))
        {
                if (living(target))
                {
                        tell_object(target, HIR "忽然間，眼前慢慢明亮了起來，能看見了。\n" NOR);
                }
                delete_temp("block_msg/all", target);
               target->clear_condition("no_perform");
                delete_temp("daojian_cimu", target);
        }
        return;
}
