#include <ansi.h>
inherit FORCE;

int valid_enable(string usage)
{
        // return usage == "force" || usage == "parry";
        return usage == "force";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("yijin-duangu", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_force(string force)
{
        return 1;
}

mapping *action = ({
([      "action":"$N默自運功，依照易筋鍛骨的口訣將內息在周身經脈中游走了一遍"
]),
});

mapping query_action(object me, object weapon)
{
        return action[0];
}


int valid_learn(object me)
{
        if( query("gender", me) == "無性" && me->query_skill("yijin-duangu",1)>49 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的易筋鍛骨內功。\n");

        if( query("character", me) == "狡黠多變" && query("yijin-duangu", me)>199 )
                return notify_fail("這九陰真經中所記載的易筋鍛骨正大恢弘，氣度儼然，依照"
                                   "你狡黠多變的天性似乎只能學到這種程度。\n");

        if( query("character", me) == "心狠手辣" && query("yijin-duangu", me)>169 )
                return notify_fail("這九陰真經中所記載的易筋鍛骨正大恢弘，氣度儼然，依照"
                                   "你心狠手辣的天性似乎只能學到這種程度。\n");

        if( query("character", me) == "陰險狡詐" && query("yijin-duangu", me)>139 )
                return notify_fail("這九陰真經中所記載的易筋鍛骨正大恢弘，氣度儼然，依照"
                                   "你陰險狡詐的天性似乎只能學到這種程度。\n");
          if( query("con", me)<30 )
                  return notify_fail("你覺得自己先天根骨不足，一時難以修煉。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候還不夠，還不能學習易筋鍛骨內功。\n");

        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("yijin-duangu", 1))
                return notify_fail("你覺得自己的武學修養有限，難以領會更高深的易筋鍛骨。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("易筋鍛骨內功只能用學(learn)的來增加熟練度。\n");
        if( query("qi", me)<150 )
                return notify_fail("你的體力太差了，不能練習易筋鍛骨。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力太差了，不能練習易筋鍛骨。\n");

        me->receive_damage("qi", 100);
        addn("neili", -150, me);
        return 1;
}

/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("yijin-duangu", 1) < 100 ||
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force", 1) + mp;
        dp = me->query_skill("parry", 1);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIM"$n單手接下了$N這一招，卻發出「鏘」一聲，"
                                            HIM"彷彿$n這隻手是鐵鑄般。\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM"$N一招平實得打在$n身上，然而$N感覺像打到"
                                            HIM"棉花上一樣，説不出的怪異。\n"NOR]);
                        break;
                default:
                        result += (["msg" : HIM"眼看$N這招逼得$n無路可逃，卻見$n沒了骨頭"
                                            HIM"似的直攤了下去，使$N這招無功而返。\n"NOR]);
                        break;
                }
                return result;
        }
}
*/

string exert_function_file(string func)
{
        return __DIR__"yijin-duangu/" + func;
}
