// This is player's own perform (Write by Lonely@nt2)
//Createby虛寧(Ningbufan)atTue May 10 12:50:25 2011
// 仁劍震音揚(renjian)
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "仁劍震音揚" NOR; }

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int attack;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (member_array("sword", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if( !objectp(weapon=query_temp("weapon", me) )
                    || query("skill_type", weapon) != "sword" )
                        return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                        return notify_fail(name() + "只能空手使用。\n");
        }

        if ((int)me->query_skill("sanda-sword", 1) < 400)
                return notify_fail("你" + to_chinese("sanda-sword") + "不夠嫻熟，難以施展" + name() + "。\n");

        if (member_array("sword", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("sword") != "sanda-sword")
                        return notify_fail("你沒有準備" + to_chinese("sanda-sword") + "，難以施展" + name() + "。\n");
        }

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N面露悲憫，雙腳站立不動，劍柄抵住額頭，口中念念有辭，持劍如持香，只見$N兩手掌心向外，以黏勁吸住劍柄，內力發動，劍刃旋轉如盤，望之如同月輪。這劍轉動快速勁急，卻不聞分毫破空之聲，金輪蓋頂，熱氣飄盪，彷佛佛頂光暈一般，便在此時，那光暈往外膨脹，登將$n整個人包在圈內" + "\n" + NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 90, HIM "只聽叮叮當當之聲不絕于耳，無數斷劍已然跌落地面，一聲慘嚎，跟著$n口吐鮮血，跪倒在地。" + "\n" NOR);
                addn("neili", -200, me);
                me->start_busy(1);
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p見勢不妙，抽身急退，險險避過$P的這記殺招，塵土飛揚中，地上裂開了一道大口子！" + "\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_sort(msg, me, target);
        return 1;
}
