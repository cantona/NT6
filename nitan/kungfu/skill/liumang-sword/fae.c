// zhenwu.c 太極劍法「真武除邪」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「真武除邪」只能對戰鬥中的對手使用。\n");
                
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法使用「流氓發惡」。\n");

        msg = HIY "$N" HIY "突然抽劍待步，左手耍出一個白色氣團，叱吒的氣團看起來就像一個無極盤旋向$n" HIY "。\n" NOR;

        addn("neili", -50, me);
        ap = me->query_skill("sword", 1) / 2 +
        me->query_skill("taiji-jian", 1);
        dp = target->query_skill("parry");
        if (target->is_bad()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企圖，鎮"
                       "定逾恆，全神應對自如。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return
                HIR "$p" HIR "驚慌失措，呆在當場，被$P"
                HIR "這一掌擊中要害！後面隨之而來的流氓劍又直刺向胸前，頓時不知如何抵擋！\n" NOR;
}
