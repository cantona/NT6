// po.c 獨孤九劍

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIW "破眾式" NOR; }

int perform(object me, object target)
{
        string msg;
        string *learned;
        object weapon, weapon2;
        string type;
        mapping prepare;
        int n;
        int skill, ap, dp, damage, ss;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("lonely-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("獨孤九劍只能對戰鬥中的對手使用。\n");

        if (skill < 50)
                return notify_fail("你的獨孤九劍等級不夠，練好了再來！\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        weapon2=query_temp("weapon", target);
        prepare = target->query_skill_prepare();
        if( weapon2)type=query("skill_type", weapon2);
        else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
        else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
        else if (sizeof(prepare) == 2)
                    type = (keys(prepare))[query_temp("action_flag",target)]; 

        ap = skill + me->query_skill("sword", 1) / 2;
        learned=query("can_perform/dugu-jiujian", me);
        if (arrayp(learned) && member_array(type, learned) != -1)
                ap *= 2;

        ss = target->query_skill("never-defeated", 1) * 11 / 10;
        if (ss < target->query_skill("lonely-sword", 1))
                  ss = target->query_skill("lonely-sword", 1);
        if (ss < target->query_skill("pixie-jian", 1))
                  ss = target->query_skill("pixie-jian", 1);

        dp = target->query_skill(type, 1) * 2 + ss * 2;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIC "$N" HIC "隨意揮灑手中的" + weapon->name() + HIC
                      "，招招從出其不意的方位直指$n" HIC +
                      to_chinese(type)[4..<1] + "中的破綻。\n" NOR;
                n = 3 + random(5);
                if (ap / 3 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "大吃一驚，慌亂之下破綻迭出，$N" HIY "唰唰連攻" +
                               chinese_number(n) + "劍！\n" NOR;
                        message_combatd(msg, me, target);
                        me->start_busy(1 + random(n));
                        while (n-- && me->is_fighting(target))
                        {
                                if (! target->is_busy() && random(2))
                                        target->start_busy(1);
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }

                        if (weapon2 && random(ap) > dp && type != "pin")
                        {
                                msg = HIW "\n$n" HIW "覺得眼前眼花繚亂，手中的" + weapon2->name() +
                                      HIW "一時竟然拿捏不住，脱手而出！\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "\n$n略得空隙喘息，一時間卻也無力反擊。\n" NOR;
                        }
                } else
                {
                        msg += HIY "$n" HIY "連忙抵擋，一時間不禁手忙腳亂，無暇反擊。\n" NOR;
                        me->start_busy(1);
                        if (! target->is_busy())
                        target->start_busy(1 + random(skill / 20));
                }
        } else
        {
                msg = HIC "$N" HIC "拿着手中的" + weapon->name() + HIC "，東戳西指，"
                      "不過$n" HIC "防守的異常嚴密，$N" HIC "一時竟然無法找到破綻。\n" NOR;
                me->start_busy(3 + random(2));
                if (! target->is_busy())
                target->start_busy(1);
        }

        message_combatd(msg, me, target);
        return 1;
}
