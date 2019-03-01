#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "亢龍有悔" NOR "」"
#define HUIP "「" HIR "亢龍有悔" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xianglong-zhang/hui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUI "只能空手使用。\n");

        if ((int)me->query_skill("force") < 380)
                return notify_fail("你內功修為不夠，難以施展" HUI "。\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("你內力修為不夠，難以施展" HUI "。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 250)
                return notify_fail("你降龍十八掌火候不夠，難以施展" HUI "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你沒有激發降龍十八掌，難以施展" HUI "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你沒有準備降龍十八掌，難以施展" HUI "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        // 第一掌
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("dodge")+query("dex", target)*5;

        message_sort(HIW "\n忽然$N" HIW "身形激進，左手一劃，右手呼的一掌"
                     "拍向$n" HIW "，正是降龍十八掌" HUIP "。力自掌生之際"
                     "說到便到，以排山倒海之勢向$n" HIW "狂湧而去，當真石"
                     "破天驚，威力無比。\n" NOR, me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(10),
                                          HIR "$P身形一閃，竟已晃至$p跟前，$p躲"
                                          "閃不及，頓被擊個正中。\n" NOR);
        } else
        {
                msg = HIC "卻見$p氣貫雙臂，凝神應對，$P掌"
                      "力如泥牛入海，盡數卸去。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第二掌
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("parry")+query("int", target)*5;

        message_sort(HIW "\n$N" HIW "一掌既出，身子已然搶到離$n" HIW "三"
                     "四丈之外，後掌推前掌兩股掌力道合並，又是一招" HUIP
                     "攻出，掌力猶如怒潮狂湧，勢不可當。霎時$p便覺氣息窒"
                     "滯，立足不穩。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                          HIR "$p一聲慘嚎，被$P這一掌擊中胸前，"
                                          "喀嚓喀嚓斷了幾根肋骨。\n" NOR);
        } else
        {
                msg = HIC "可是$p全力抵擋招架，竟似遊刃有"
                      "余，將$P的掌力卸于無形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第三掌
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("force")+query("con", target)*5;

        message_sort(HIW "\n緊跟著$N" HIW "右掌斜揮，前招掌力未消，此招掌"
                     "力又到，竟然又攻出一招" HUIP "，掌夾風勢，勢如破竹，"
                     "便如一堵無形氣牆，向前疾沖而去。$n" HIW "只覺氣血翻"
                     "湧，氣息沉濁。\n" NOR, me, target);

        if (ap *11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIR "結果$p躲閃不及，$P掌勁頓時穿胸而"
                                          "過，頓時口中鮮血狂噴。\n" NOR);
        } else
        {
                msg = HIC "$p眼見來勢兇猛，身形疾退，瞬間"
                      "飄出三丈，脫出掌力之外。\n" NOR;
        }
        message_vision(msg, me, target);
        me->start_busy(3 + random(4));
        addn("neili", -400-random(600), me);
        return 1;
}