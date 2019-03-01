// baibu.c 百步穿楊

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("百步穿楊只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            ! weapon->is_arrow())
                return notify_fail("你現在手中並沒有拿著箭，怎麼施展百步穿楊？\n");

        if (weapon->query_amount() < 3)
                return notify_fail("至少要有一支箭你才能施展百步穿楊。\n");

        if ((skill = me->query_skill("xuanyuan-arrow", 1)) < 100)
                return notify_fail("你的軒轅箭法不夠嫻熟，不會使用百步穿楊。\n");

        if( query("neili", me)<100 )
                return notify_fail("你內力不夠了。\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg= HIY "突然間，$N" HIY "幾個筋鬥倒翻而去，已在$n" HIY
             "數丈之外。$n" HIY "正待追擊，$N" HIY "忽然轉身，好一個「百步穿楊」！\n"
             HIY "說時遲，那時快，" HIY + weapon->name() + HIY "已帶著破空之聲，直射$n"
             HIY "面門！\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        ob_exp=query("combat_exp", target);
        if (random(my_exp) > ob_exp)
        {
                msg += HIR "結果$p" HIR "反應不及，中了$P" + HIR "一箭！\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me, target,
                               query("jiali", me)+120);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "可是$p" CYN "從容不迫，輕巧的閃過了$P"
                       CYN "這一箭。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}