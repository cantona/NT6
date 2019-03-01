//wai-bagua.c 外八卦

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
        "可是卻被$n利用八卦四方的巧勁輕輕御開，化解了$N這一擊。\n",
        "但是被$n手中兵刃利用八卦勁巧妙地卸開。\n",
        "但是$n按照八卦方位，隨手轉動手中的$p，讓$N只感無從下手。\n",
});

string *unarmed_parry_msg = ({
        "可是卻被$n利用八卦四方的巧勁輕輕御開，化解了$N這一擊。\n",
        "$n身形一轉，雙手按照八卦方位打出，使得$N所有的攻勢全部落空。\n",
        "但是$N感覺像打到棉花上一樣，力道已全被$n利用八卦勁卸去。\n",
});

string query_parry_msg(object weapon)
{
        if (weapon)
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int valid_enable(string usage)
{
        return usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("bagua-bu", 1) < 100)
                return notify_fail("你的八卦步火候還不夠，不能學習外八卦。\n");

        if ((int)me->query_skill("bagua-quan", 1) < 100)
                return notify_fail("你的八卦拳火候還不夠，不能學習外八卦。\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 100)
                return notify_fail("你的八卦掌火候還不夠，不能學習外八卦。\n");

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本招架技巧掌握的還不夠熟練，無法學習外八卦。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("wai-bagua", 1))
                return notify_fail("你的基本招架水平有限，無法領會更高深的外八卦。\n");

        return 1;
}

int practice_skill(object me)
{
        if (me->query_skill("wai-bagua", 1) < 100)
                return notify_fail("你對外八卦神功的了解甚淺，還不足以自行鍛煉。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練護體神功。\n");

        me->receive_damage("qi", 50);
        addn("neili", -60, me);
        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int) me->query_skill("wai-bagua", 1) < 100
           || ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("wai-bagua", 1);

        if (ap / 2 + random(ap) < dp * 3 / 4)
        {
                result = ([ "damage" : -damage ]);

                switch(random(3))
                {
                case 0:
                        result += ([ "msg" : WHT "$n" WHT "身形忽然按照八卦方"
                                             "位轉個不停，$N" WHT "這一招竟然"
                                             "無從下手。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : WHT "$n" WHT "單掌利用八卦四方的"
                                             "巧勁輕輕一托，$N" WHT "登時拿捏"
                                             "不準力道，不禁泛起一陣有心無力"
                                             "的感覺。\n" NOR ]);
                        break;

                default:
                        result += ([ "msg" : WHT "$N" WHT "一招眼看擊中了$n"
                                             WHT "，然而$n" WHT "輕輕一格，"
                                             "將$N" WHT "的攻擊利用八卦巧勁"
                                             "化于無形。\n" NOR ]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "輕輕揮拳阻擱，暗含八卦巧勁，可$N"
                                 HIY "精通易理，絲毫不假思索，隨即反身出招。\n" NOR;
                        break;
                default:
                        result = HIY "$n" HIY "按照八卦陣方位轉個不停，可卻見$N"
                                 HIY "一聲冷笑，順手便是一招，恰好破盡玄機。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("wai-bagua", 1);
        if (lvl < 100) return 0;
        if (lvl < 150) return 20;
        if (lvl < 200) return 40;
        if (lvl < 250) return 50;
        if (lvl < 300) return 60;
        if (lvl < 350) return 70;
        return 80;
}

string perform_action_file(string action)
{
        return __DIR__"wai-bagua/" + action;
}