#include <ansi.h>
inherit SKILL;

string *parry_msg = ({
        "卻見$n雙手輪轉，護住周身，頓時將$N的招數全全封鎖。\n",
        "但是$n身形急變，內勁迸發，將$N的攻勢阻隔開來。\n",
        "但是$n身子微側，雙手同時一撥，已將$N的招數卸於無形。\n",
});

string query_parry_msg(object weapon)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_enable(string usage)
{
        return usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("taoism", 1) < 150)
                return notify_fail("你對道學理解不夠深入，無法學習金關玉鎖。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的基本內功火候不夠，無法學習金關玉鎖。\n");

        if ((int)me->query_skill("parry", 1) < 150)
                return notify_fail("你的基本招架火候不夠，無法學習金關玉鎖。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你目前的內力修為不足，無法學習金關玉鎖。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("jinguan-yusuo", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的金關玉鎖。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("jinguan-yusuo", 1))
                return notify_fail("你的基本招架水平有限，無法領會更高深的金關玉鎖。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("jinguan-yusuo", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("jinguan-yusuo", 1);

        // 因為後期可以練習，所以保證出現卸招的機率低
        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage" : -damage ]);

                switch (random(3))
                {
                case 0:
                        result += ([ "msg" : YEL "$n" YEL "面含微笑，雙手回"
                                             "圈，頓時將$N" YEL "的招數全全"
                                             "鎖死。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : YEL "$n" YEL "單掌輕輕撩起，掌"
                                             "勁吞吐，竟憑空架起一道氣牆，將$N"
                                             YEL "的攻勢全然阻隔在外。\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : YEL "卻見$n" YEL "掌出如風，飄"
                                             "忽不定，輕描淡寫將$N" YEL "的"
                                             "攻擊卸之於無形。\n" NOR ]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "雙手迴圈，企圖鎖死$N" HIY "的"
                                 "招數，可陡然間卻見$N" HIY "撤手迴轉，再攻出"
                                 "一招。\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "單掌輕輕撩起，欲以內勁阻擋$N"
                                 HIY "的攻勢，可$N" HIY "驀的變招，從另一方"
                                 "位攻入。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "掌出如風，飄然護住全身，可$N"
                                 HIY "理也不理，只管運足內勁，中破攻入。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int practice_skill(object me)
{
        if (me->query_skill("jinguan-yusuo", 1) < 200)
                return notify_fail("你對金關玉鎖瞭解甚淺，不足以自行鍛鍊。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinguan-yusuo/" + action;
}