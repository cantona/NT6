// This program is a part of NITAN MudLIB
// zhen.c 一掌震天

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "一掌震天"; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;

        if (! target)
                target = offensive_target(me);

        if (! target || ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail("「一掌震天」只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須空手才能使用「一掌震天」之力！\n");

        if (me->query_skill("liuyang-zhang", 1) < 200)
                return notify_fail("你的天山六陽掌不夠嫻熟，無法使用「一掌震天」之力。\n");

        if (me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法不夠嫻熟，無法使用「一掌震天」之力。\n");

        if (me->query_skill("force", 1) < 220)
                return notify_fail("你的基本內功修為不足，無法使用「一掌震天」之力。\n");

        if (me->query_skill("bahuang-gong", 1) < 240)
                return notify_fail("你的八荒六合惟我獨尊功修為不足，無法使用「一掌震天」之力。\n");

        if (me->query_str() < 38)
                return notify_fail("你的後天膂力不足，無法使用「一掌震天」之力。\n");

        if (me->query_str() < 38)
                return notify_fail("你的後天根骨不足，無法使用「一掌震天」之力。\n");

        if( query("neili", me)<2000 )
                return notify_fail("你現在內力不足，不能使用「一掌震天」。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你現在內力修為不足，不能使用「一掌震天」。\n");

        if( query("jiali", me)<50 )
                return notify_fail("你加力這麼小，怎麼能施展「一掌震天」呢？\n");


        msg = WHT" \n只見$N" WHT "忽然掌緣隱隱泛出殷紅之色，絲絲白氣繚繞其間，轉瞬間已將$P的手掌包了起來。\n" +
             "待得此時，$n" WHT "已覺不妙，哪知正待閃躲，$N" WHT "這招「" HIY "一掌震天" WHT "」已然推至胸前，來勢雖\n" +
             "緩，但$p只覺身周的空氣仿佛已經凝結，這一掌之力已將上下左右前後包了起來，實是難\n"+
             "以擺脫。瞬間的空氣流動直如一個真空大洞，使得身周的人均覺得一陣氣滯！\n\n"NOR;

        ap = attack_power(me, "strike") + me->query_con()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                addn("neili", -500, me);

                pmsg = HIR "$n" HIR "眼見$N" HIR "一招已至，掌勁如洪，內力澎湃，然而苦于身陷旋渦之中，避無可避，只是\n" +
                       "稍微挪動腳步也已困難之極，結果被$N" HIR "一掌印在胸前，登感一陣痛入骨髓，卻是肋骨被\n" +
                       "這一掌之力震斷，氣血翻湧已然失控，一口鮮血如箭般從口鼻中噴了出來！\n\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65, pmsg);

                me->start_busy(3);
        } else
        {
                msg += HIG "豈料$n" HIG "機敏異常，一眼道破$N" HIG "這招的破綻之處乃是旋渦的中心，其間極為薄弱，于是\n"+
                       "單手成指，竟刺破$N" HIG "的旋渦屏障，接連兩指點在$P手心的" HIR "少府"
                       HIG "、" HIR "勞宮" HIG "二穴！結果$N" HIG "穴道被\n" +
                      "封，這內力無處宣泄，竟反蝕其身，震得$P臉如金紙，口唇紫青，查點受了內傷！\n\n" NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
