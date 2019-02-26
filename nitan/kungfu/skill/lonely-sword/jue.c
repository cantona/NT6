// This program is a part of NITAN MudLIB
// jue.c 「總訣式」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "總訣式"; }

int perform(object me)
{
        string msg;
        object weapon;
        int skill, jing_cost;
        int improve;

        skill = me->query_skill("lonely-sword", 1);
        jing_cost=45-query("int", me);
        if (jing_cost < 5) jing_cost = 5;

        if( query("no_fight", environment(me)) && query("doing", me) != "scheme" )
                return notify_fail("這裏太嘈雜，你不能靜下心來演練。\n");

        if (me->is_fighting())
                return notify_fail("「總訣式」不能在戰鬥中演練。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你必須先去找一把劍。\n");

        if (! skill || skill < 20)
                return notify_fail("你的獨孤九劍等級不夠, 不能演練「總訣式」！\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠，沒有力氣演練「總訣式」！\n");

        if( query("jing", me)<-jing_cost )
                return notify_fail("你現在太累了，無法集中精神演練「總訣式」！\n");

        if (me->query_skill("lonely-sword", 1) > 600 &&
            me->query_skill("lonely-sword", 1) > me->query_skill("sword", 1))
                return notify_fail("你的劍法不夠，無法使用「總訣式」來提高獨孤九劍！\n");

        if (me->query_skill("lonely-sword", 1) > 800)
                return notify_fail("獨孤九劍演練已經到了極限，需要研究才能提高等級！\n");

        if (! me->can_improve_skill("lonely-sword"))
                return notify_fail("你的實戰經驗不夠，無法體會「總訣式」！\n");

        msg = HIG "$N" HIG "使出獨孤九劍之「總訣式」，將手中" +
              weapon->name() + HIG "隨意揮舞擊刺。\n" NOR;
        message_combatd(msg, me);

        addn("neili", -50, me);
        me->receive_damage("jing", jing_cost);

        if (skill < 60)
           improve = 10; else
        if (skill < 90)
           improve = 10 + random((int)me->query_int() - 9); else
        if (skill < 140)
           improve = 10 + random((int)me->query_int() * 2 - 9); else
        if (skill < 200)
           improve = 10 + random((int)me->query_int() * 4 - 9); else
           improve = 10 + random((int)me->query_int() * 8 - 9);

        tell_object(me, MAG "你的「基本劍法」和「獨孤九劍」進步了！\n" NOR);
        me->improve_skill("sword", improve);
        me->improve_skill("lonely-sword", improve * 3 / 2);
        me->start_busy(random(2));
        return 1;
}