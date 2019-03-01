// zhong.c 種生死符

#include <ansi.h>

inherit F_SSERVER;

string name() { return "種生死符"; }

int perform(object me, object target)
{
        int ap, dp, lvl;
        object obj;
        string msg;

        if (! target) target = offensive_target(me);

        if (! objectp(target) || target == me
         || query("id", target) == "muren" )
                return notify_fail("你要往誰身上種生死符？\n");

        lvl  = me->query_skill("liuyang-zhang", 1);

        if (! me->is_fighting() || ! target->is_fighting() || ! living(target))
                return notify_fail("你必須在戰鬥中才能種生死符！\n");

        if (! objectp(obj=present("jiudai", me)))
                return notify_fail("你身上沒有酒袋，不能化水為冰。\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 150
                && (int)me->query_skill("beiming-shengong", 1) < 150)
                return notify_fail("你的逍遙派內功功力不夠，不能種生死符！\n");

        if (me->query_skill_mapped("force") != "bahuang-gong"
        &&  me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你沒有運用逍遙派內功！\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 150)
                return notify_fail("你的天山六陽掌功力不夠，不能種生死符！□n");

        if( query("neili", me)<1000 )
                return notify_fail("你的內力不夠，不能種生死符。\n");

        message_combatd(
                WHT "$N突然從背後掏出一個酒袋，往自己掌心倒了些酒水。"
                "$N左掌掌心中暗運內功，逆轉真氣，\n不多時已將掌中酒水化成七八片寒冰，右掌"
                "蘊出一縷白線，猛地向$n的胸口射了過去！\n\n" NOR,
                me, target );

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "只覺胸口一悶，一絲涼意直入肺腑，腦中一片空白茫然不知所措！\n" NOR;

                target->affect_by("ss_poison",
                                  ([ "level" : lvl * 2,
                                     "id":query("id", me),
                                     // "remain": -1,
                                     "duration" : lvl / 100 + random(lvl / 10) ,
                                  ]));

                if (! target->is_busy())
                                target->start_busy(2);
                me->start_busy(2);
        } else
        {
                me->start_busy(2);
                msg = CYN "可是$n" CYN "見勢不妙，猛一運力把白線逼了回去。\n" NOR;
                tell_object(me, HIG "你覺得手指一陣冰涼，暗叫一聲不好，趕經運功抵抗！\n" NOR);
        }
        message_combatd(msg, me, target);

        me->want_kill(target);
        if (! target->is_killing(me)) target->kill_ob(me);

        return 1;
}


