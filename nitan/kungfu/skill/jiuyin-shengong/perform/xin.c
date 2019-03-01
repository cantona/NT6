#include <ansi.h>
#include <combat.h>

#define XIN "「" HIR "攝心大法" NOR "」"

inherit F_SSERVER;

void remove_effs(object target);

string final(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp, damage;
        int times;

        me = this_player();

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIN "只能在戰鬥中對對手使用。\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 280)
                return notify_fail("你九陰神功不夠嫻熟，難以施展" XIN "。\n");
 
        if ((int)me->query_skill("force", 1) < 280)
                return notify_fail("你內功根基不夠，難以施展" XIN "。\n");   

        if (me->query_skill_mapped("force") != "jiuyin-shengong")
                return notify_fail("你沒有激發九陰神功為內功，難以施展" XIN "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" XIN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");
                            
        msg = HIM "\n$N" HIM "猛然間尖嘯一聲，施展出九陰神功中的「" HIR "攝心大法" HIM"」。"
              "只見$N" HIM "各種招式千奇百怪、變化多端，臉上喜怒哀樂，怪狀百出。\n" NOR;

        ap = attack_power(me, "force");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
             msg += HIG "$n" HIG "登時覺得胸口苦悶之極，心神難以自制，喜怒哀樂竟全隨著$N" HIG
                    "而變。頃刻之間，$n" HIG "頓覺精力不濟，頭暈目眩。\n" NOR; 

             me->start_busy(2 + random(4));
             addn("neili", -400, me);
             if (! target->is_busy())
             target->start_busy(2 + random(4));
             target->receive_damage("jing", ap / 5 + random(ap / 4) );
             target->receive_wound("jing", ap / 5 + random(ap / 8) );
             set_temp("eff/jiuyin-shengong/xin", 1, target);

             if (target->query_skill("martial-cognize", 1) < 200)times =  ap / 10 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 200)times = ap / 11 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 220)times = ap / 12 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 260)times = ap / 14 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 300)times = ap / 16 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 340)times = ap / 18 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 360)times = ap / 22 + random(6);
             if (target->query_skill("martial-cognize", 1) >= 380)times = ap / 30 + random(6);
             if (target->query_skill("martial-cognize", 1) > 400)times = 8 + random(7);
             remove_call_out("remove_effs");
             call_out("remove_effs", times, target);         

        } else
        {
              msg += NOR + CYN "$n" NOR + CYN "怒喝道：“爾等妖法，休想迷惑我！”。猛然間，招式陡快，"
                     "竟將$N" NOR + CYN "這招破去。\n" NOR;
              addn("neili", -200, me);
              me->start_busy(1 + random(2));
        }
        message_sort(msg, me, target);

        return 1;
}

void remove_effs(object target)
{
        if( !objectp(target) || !query_temp("eff/jiuyin-shengong/xin", target))return ;
        delete_temp("eff/jiuyin-shengong/xin", target);
        tell_object(target, HIW "猛然間你氣血上沖，頭昏脹痛之感頓然消去，精力逐漸集中起來。\n" NOR);
        return;      
}