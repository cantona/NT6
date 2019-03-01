// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define QI "「" HIW "破氣式" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, skill;
        int damage;

        if( userp(me) && query("can_perform/dugu/qi", me)<100 )
                return notify_fail("你目前還不會施展" QI "。\n");

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("dugu-jiujian", 1);

        if (! me->is_fighting(target))
                return notify_fail(QI "只能對戰鬥中的對手使用。\n");

        if (skill < 120)
                return notify_fail("你獨孤九劍等級不夠，無法施展" QI "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，無法施展" QI "。\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian") 
                return notify_fail("你沒有激發獨孤九劍，無法施展" QI "。\n");

        /*
        if (target->query_condition("no_exert"))
                return notify_fail("對方現在已經無法控制真氣，放膽攻擊吧。\n");
        */
        
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "施出獨孤九劍「破氣式」，手中" + weapon->name() +
              HIW "中攻直進，遙指$n" HIW "的氣海要穴。\n" NOR;

        ap = attack_power(me, "sword") + me->query_skill("parry");
        dp = defense_power(target, "force") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else 
        {
                msg += CYN "可$n" CYN "深知$N" CYN "這招的厲"
                       "害，當即向後橫移數尺，躲閃開來。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int ap)
{
        if (target->query_condition("no_exert")) 
                return "";
        target->apply_condition("no_exert", 10);
        call_out("poqi_end", 10 + random(ap / 30), me, target);
        return  HIR "$n" HIR "被$N" HIR "一劍劃過氣門，登感一陣"
                "錐心的刺痛，全身真氣源源而瀉！\n" NOR;
}

void poqi_end(object me, object target)
{
        if (target && target->query_condition("no_exert"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口氣，臉色由"
                                        "白轉紅，看起來好多了。\n" NOR, target);

                        tell_object(target, HIY "你感到被擾亂的真氣慢慢平靜"
                                            "了下來。\n" NOR);
                }
                target->clear_condition("no_exert");
        }
        return;
}
