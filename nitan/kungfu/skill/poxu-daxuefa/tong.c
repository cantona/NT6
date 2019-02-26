#include <ansi.h>
#include <combat.h>

#define TONG "「" HIR "破元通虛" NOR "」"

inherit F_SSERVER;

string final(object me, object target, int damage);

string *finger_name = ({ "左手中指", "左手無名指", "左手食指",
                         "右手中指", "右手無名指", "右手食指", }); 

int perform(object me, object target)
{
        object weapon;
        string wp, msg;
        int ap, dp, skill;
        int damage;

        if( userp(me) && !query("can_perform/poxu-daxuefa/tong", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("poxu-daxuefa", 1);

        if (! me->is_fighting(target))
                return notify_fail(TONG "只能對戰鬥中的對手使用。\n");

        if (skill < 120)
                return notify_fail("你破虛打穴法等級不夠，無法施展" TONG "。\n");

        weapon=query_temp("weapon", me);

        if( weapon && query("skill_type", weapon) != "dagger" )
                return notify_fail("你所使用的武器不對，無法施展" TONG "。\n");

        if (weapon && me->query_skill_mapped("dagger") != "poxu-daxuefa")
                return notify_fail("你沒有激發破虛打穴法，無法施展" TONG "。\n");

        if (! weapon && me->query_skill_prepared("finger") != "poxu-daxuefa")
                return notify_fail("你沒有準備破虛打穴法，無法施展" TONG "。\n");

        if( query_temp("no_exert", target) )
                return notify_fail("對方現在已經無法控制真氣，放膽攻擊吧。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，無法施展" TONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        if (weapon)
                wp = "手中" + weapon->name();
        else
                wp = finger_name[random(sizeof(finger_name))];

        msg = HIG "$N" HIG "翻轉" + wp + HIG "，接連變化數種打穴手法，一式「"
              HIR "破元通虛" HIG "」直搗$n" HIG "胸前要穴。\n" NOR;

        ap = me->query_skill("poxu-daxuefa", 1);
        dp = target->query_skill("force", 1);

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                                           (: final, me, target, damage :));
                addn("neili", -100, me);
                me->start_busy(3);
        } else
        {
                msg += CYN "可是$n" CYN "早已看破$N"
                       CYN "招中虛實，單手一揮，登將這招化於無形。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int ap)
{
        set_temp("no_exert", 1, target);
        call_out("poqi_end", 10 + random(ap / 25), me, target);
        return  HIR "$n" HIR "只覺胸口一麻，已被$N" HIR "點中"
                "要穴，登時全身真氣阻滯，苦不堪言！\n" NOR;
}

void poqi_end(object me, object target)
{
        if( target && living(target) && query_temp("no_exert", target) )
        {
                message_combatd(HIC "$N" HIC "深深吸入一口氣，臉色由"
                                "白轉紅，看起來好多了。\n" NOR, target);

                delete_temp("no_exert", target);
                tell_object(target, HIY "你感到被擾亂的真氣慢慢平靜"
                                    "了下來。\n" NOR);
        }
        return;
}