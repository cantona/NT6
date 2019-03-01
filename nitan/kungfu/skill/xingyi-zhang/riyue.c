// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "日月同輝"; }

int perform(object me, object target)
{
        string msg;
        int i, ap, dp;

        i = me->query_skill("xingyi-zhang", 1) / 10;

        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「日月同輝」只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「日月同輝」時雙手必須空著！\n");

        if( (int)me->query_skill("xingyi-zhang", 1) < 180 )
                return notify_fail("你的星移掌不夠嫻熟，不會使用「日月同輝」。\n");

        if( (int)me->query_skill("shenyuan-gong", 1) < 180 )
                return notify_fail("你的神元功等級不夠，不能使用「星光點點」。\n");

        if( (int)me->query_dex() < 25 )
                return notify_fail("你的身法不夠強，不能使用「日月同輝」。\n");

        if (me->query_skill_prepared("strike") != "xingyi-zhang"
        ||  me->query_skill_mapped("strike") != "xingyi-zhang")
                return notify_fail("你現在無法使用「日月同輝」進行攻擊。\n");


        if( query("neili", me)<700 )
                return notify_fail("你現在內力太弱，不能使用「日月同輝」。\n");
        addn("neili", -300, me);

        message_combatd(CYN "\n$N雙掌一搓，在雙掌之間形成一個耀眼的「"HIW"氣旋"CYN"」！\n" NOR,me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", i, me);

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR"$N雙掌收在胸前，移形換步閃電般將「"HIW"氣旋"HIR"」擊向$n的檀中穴！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                msg = HIG"緊接著$N抽出左掌，身形一矮，由下而上猛襲向$n的小腹！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                msg = HIR"只見$N右掌隨後而至，凌空一躍，猶如晴空霹靂拍向$n的頭部！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                msg = HIY"$N在空中一個回轉，攜「"HIR"日月之光"HIY"」, 雙掌按向$n的丹田！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

        } else
        {
                msg = HIR"$N雙掌收在胸前，移形換步閃電般將「"HIW"氣旋"HIR"」擊向$n的檀中穴！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                msg = HIG"緊接著$N抽出左掌，身形一矮，由下而上猛襲向$n的小腹！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                msg = HIR"只見$N右掌隨後而至，凌空一躍，猶如晴空霹靂拍向$n的頭部！"NOR;
                message_combatd(msg, me, target);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

                call_out("perform2", 3, me, target);
        }
        message_combatd(YEL "\n$N一式「日月同輝」發揮的淋漓盡致，雙掌一分，氣定神閒，信心倍增。\n" NOR,me, target);
        addn("neili", -400, me);
        addn_temp("apply/dex", -i, me);
        addn_temp("apply/unarmed_damage", -i, me);
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -i, me);
        me->start_busy(2+random(2));

        return 1;
}
int perform2(object me, object target)
{
        string msg;
        int i;
        if( !me ) return 1;
        i = me->query_skill("xingyi-zhang", 1)/10;
        if (!me || !target) return 0;
        if(!living(target))
                return notify_fail("對手已經不能再戰鬥了。\n");

        if( query("neili", me)<300 )
               return notify_fail("你待要再出第二劍，卻發現自己的內力不夠了！\n");

        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", i, me);
        msg = HIY"$N在空中一個回轉，攜「"HIR"日月之光"HIY"」, 雙掌按向$n的丹田！"NOR;
        message_combatd(msg, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

        msg = HIC"只見$N斜身半轉，陡地拍出兩掌，蓄勢凌厲，直指$n左脅！"NOR;
        message_combatd(msg, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

        msg = HIW"$N將神元神功發揮到極限，幻化出漫天掌影，向$n全身籠罩過去！"NOR;
        message_combatd(msg, me, target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK);

        addn("neili", -400, me);
        addn_temp("apply/dex", -i, me);
        addn_temp("apply/unarmed_damage", -i, me);
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -i, me);
        me->start_busy(2+random(2));

        return 1;
}

