// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define PO "「" HIR "總破式" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        string *learned;
        object weapon, weapon2;
        string type;
        mapping prepare;
        int n;
        int skill, ap, dp, damage, ss;

        if( userp(me) && query("can_perform/dugu/po", me)<100 )
                return notify_fail("你還沒有受過高人指點，無法施展" PO "。\n"); 

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian", 1);

        if (! me->is_fighting(target))
                return notify_fail(PO "只能對戰鬥中的對手使用。\n");

        if (skill < 150)
                return notify_fail("你的獨孤九劍等級不夠，無法施展" PO "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，無法施展" PO "。\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian") 
                return notify_fail("你沒有激發獨孤九劍，無法施展" PO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        weapon2=query_temp("weapon", target);
        prepare = target->query_skill_prepare();

        if( weapon2)type=query("skill_type", weapon2);
        else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
        else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
        else if (sizeof(prepare) == 2) 
                  type = (keys(prepare))[query_temp("action_flag",target)]; 

        ap=skill*3/2+me->query_skill("sword",1)+query("level", me)*20+
             me->query_skill("martial-cognize", 1);

        learned=query("can_perform/dugu-jiujian", me);

        if (arrayp(learned) && member_array(type, learned) != -1)
                ap *= 2;

        ss = target->query_skill("pixie-jian", 1);

        if (ss < target->query_skill("dugu-jiujian", 1))
                  ss = target->query_skill("dugu-jiujian", 1);

        dp=target->query_skill(type,1)*2+ss+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg = HIC "$N" HIC "隨意揮洒手中的" + weapon->name() +
                      HIC "，招招從出其不意的方位直指$n" 
                      HIC + to_chinese(type)[4..<1] + "中的破綻。\n" NOR;

                n = 4 + random(4);
                if ((target->is_busy() && ap * 2 / 3 + random(ap) > dp)
                   || ap / 2 + random(ap) > dp)
                {
                        msg += HIY "$n" HIY "大吃一驚，慌亂之下破綻迭出，"
                               "$N" HIY "唰唰唰唰連攻" + chinese_number(n)
                               + "劍！\n" NOR;
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
                                msg = HIW "$n" HIW "覺得眼前眼花繚亂，手中"
                                      "的" + weapon2->name() + HIW "一時竟"
                                      "然拿捏不住，脫手而出！\n" NOR;
                                weapon2->move(environment(me));
                        } else
                        {
                                msg = HIY "$n" HIY "略得空隙喘息，一時間卻"
                                      "也無力反擊。\n" NOR;
                        }
                } else
                {
                        msg += HIY "$n" HIY "連忙抵擋，一時間不禁手忙腳亂，"
                               "無暇反擊。\n" NOR;
                        me->start_busy(1);
                        if (! target->is_busy())
                        target->start_busy(1 + random(skill / 30));
                }
        } else
        {
                msg = HIC "$N" HIC "拿著手中的" + weapon->name() +
                      HIC "，東戳西指，不過$n" HIC "防守的異常嚴密，$N"
                      HIC "一時竟然無法找到破綻。\n" NOR;
                me->start_busy(3 + random(2));
                target->start_busy(1);
        }
        message_combatd(msg, me, target);
        return 1;
}
