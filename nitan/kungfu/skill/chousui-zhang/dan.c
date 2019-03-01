#include <ansi.h>
#include <combat.h>

string name() { return HIW "煉心彈" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, fire, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        lvl = me->query_skill("chousui-zhang", 1);
        lvp = me->query_skill("poison");

        if (lvl < 120)
                return notify_fail("你的抽髓掌不夠嫻熟，難以施展" + name() + "。\n");

        if (lvp < 180)
                return notify_fail("你對毒技的了解不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("throwing") < 150)
                return notify_fail("你暗器手法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("你沒有激發抽髓掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("你沒有準備抽髓掌，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的內息不足，難以施展" + name() + "。\n");

        // 任務NPC可以直接施展
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("你必須拿著(hand)些毒藥才能施展" + name() + "。\n");

        if (objectp(du) && ! mapp(query("poison", du))) 
                return notify_fail("你手中所拿的" + du->name() + NOR "不"
                                   "是毒藥，難以施展" + name() + "。\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("將" + du->name() + NOR "彈射出去？似"
                                   "乎不太好吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        // 根據抽髓掌和毒技的不同，給予不同的信息
        if (lvl >= 200 && lvp >= 270)
        {
                pos = 600 + random(lvp * 4 / 3);
                fire = "一團瑩綠色的" HIG "碧燄" HIR;
        } else
        if (lvl >= 180 && lvp >= 240)
        {
                pos = 400 + random(lvp * 3 / 4);
                fire = "一個殷紅色的火球";
        } else
        if (lvl >= 150 && lvp >= 210)
        {
                pos = 200 + random(lvp * 2 / 3);
                fire = "數點殷紅色的" NOR + RED "火星" HIR;
        } else
        {
                pos = 100 + random(lvp / 2);
                fire = "一點暗紅色的" NOR + RED "火星" HIR;
        }

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "毒丸";

        msg = HIR "$N" HIR "單掌一抖，施出星宿派絕技「" HIW "煉心彈"
              HIR "」，將手中" + name + HIR "「嗖」的彈射了出去。\n"
              "卻見那" + name + HIR "射至中途，竟驀地爆裂開，化作" +
              fire + "飄然襲向$n" HIR "。\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // 首先判斷內力，如果對方內力過高則無效
        if (an / 2 + random(an) < dn * 2 / 3)
        {
                msg += WHT "然而$n" WHT "全然不放在心上，輕輕一抖，已將$N"
                       WHT "射來的火燄震滅。\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                ap = attack_power(me, "strike") +
                     me->query_skill("poison");

                // 將任務NPC和玩家區分，再計算防御狀況
                if (userp(me))
                        dp = defense_power(target, "dodge") +
                             target->query_skill("martial-cognize")/2;
                else
                        dp = defense_power(target, "dodge") +
                             target->query_skill("parry")/2;

                damage = damage_power(me, "strike") + pos;
                damage+= query("jiali", me);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                                  (: final, me, target, damage :));
                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "可是$n" CYN "見勢不妙，急忙騰挪身形，終"
                               "于避開了$N" CYN "射來的火燄。\n" NOR;
                        me->start_busy(3);
                        addn("neili", -100, me);
                }
        }
        message_combatd(msg, me, target);

        // 消耗毒藥數量
        if (objectp(du))
        {
                if (du->query_amount())
                {
                        du->add_amount(-1);

                        if (du->query_amount() < 1)
                                destruct(du);
                } else
                        destruct(du);
        }
        return 1;
}

string final(object me, object target, int damage)
{
        object cloth;
        string name;
        int lvp = me->query_skill("poison");

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
        if( objectp(cloth=query_temp("armor/armor", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
                name = "肌膚";

        target->affect_by("fire_poison",
                ([ "level"    : lvp * 2 + random(lvp * 3),
                   "id":query("id", me),
                   "duration" : 6 + random(lvp / 30) ]));

        target->receive_damage("jing", damage, me);
        target->receive_wound("jing", damage * 2 / 3, me);
        if( !target->is_busy() )
                target->start_busy(1);

        return  HIR "$n" HIR "一個不慎，火星頓時濺到" + name +
                HIR "之上，大勢燃燒起來，皮肉燒得嗤嗤作響。\n" NOR;
}
