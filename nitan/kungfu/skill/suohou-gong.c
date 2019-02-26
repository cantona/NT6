#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *action_msg = ({
        "$N左手揚起，右手伸出，五指曲張，對着$n的頸部便抓",
        "只見一陣勁風直逼向前$N單臂伸出，手指直取$n的哽嗓咽喉",
        "$N左手一掠，將$n防守招數盡格在外門，右手疾探而出對$n的喉頭抓到",
        "$N身形急跳，早落到$n的身後，一雙冰冷的大手抓向$n的後頸",
        "$N雙臂彎出，柔若無骨，如兩條軟鞭一般，緊緊纏住$n的脖子不放",
});

mapping *action = ({
([      "action": "$N一聲暴喝，雙手如鈎如戢，插向$n的$l",
        "force" : 100,
        "attack": 28,
        "dodge" : 17,
        "parry" : 0,
        "damage": 13,
        "lvl"   : 0,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形一躍，直撲而上，右手直直抓向$n的$l",
        "force" : 130,
        "attack": 35,
        "dodge" : 20,
        "parry" : 5,
        "damage": 20,
        "lvl"   : 10,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平伸，十指微微上下抖動，奮力抓向$n的$l",
        "force" : 160,
        "attack": 39,
        "dodge" : 32,
        "parry" : 10,
        "damage": 25,
        "lvl"   : 20,
        "damage_type" : "抓傷"
]),
([      "action": "$N悄無聲息的遊走至$n身前，猛的一爪奮力抓向$n的$l",
        "force" : 172,
        "attack": 42,
        "dodge" : 38,
        "parry" : 19,
        "damage": 29,
        "lvl"   : 40,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙手平提胸前，左手護住面門，右手陡然抓向$n的$l",
        "force" : 187,
        "attack": 45,
        "dodge" : 41,
        "parry" : 21,
        "damage": 33,
        "lvl"   : 60,
        "damage_type" : "抓傷"
]),
([      "action": "$N低喝一聲，雙手化掌為爪，一前一後抓向$n的$l",
        "force" : 203,
        "attack": 51,
        "dodge" : 49,
        "parry" : 22,
        "damage": 36,
        "lvl"   : 80,
        "damage_type" : "抓傷"
]),
([      "action": "$N右腿斜插$n二腿之間，上手取目，下手直勾$n的喉部",
        "force" : 245,
        "attack": 56,
        "dodge" : 53,
        "parry" : 27,
        "damage": 41,
        "lvl"   : 100,
        "damage_type" : "抓傷"
]),
([      "action": "$N狂喝一聲，雙爪如狂風驟雨般對準$n的$l連續抓出",
        "force" : 270,
        "attack": 61,
        "dodge" : 58,
        "parry" : 38,
        "damage": 45,
        "lvl"   : 120,
        "damage_type" : "抓傷"
])
});

int valid_enable(string usage)
{
        return usage == "claw" ||  usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鎖喉功必須空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學鎖喉功。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太弱，無法練鎖喉功。\n");

        if ((int)me->query_skill("claw", 1) < 80)
                return notify_fail("你的基本抓法不夠，無法學鎖喉功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("suohou-gong", 1))
                return notify_fail("你的基本抓法火候水平有限，無法領會更高深的鎖喉功。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

/*
mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("suohou-gong", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}
*/
mapping query_action(object me, object weapon)
{
        int lvl_temp = random((int)me->query_skill("suohou-gong", 1));
        if( lvl_temp>100 && query("neili", me)>800 )
        {
                if (lvl_temp <= 150)
                {
                        addn("neili", -50, me);
                        return ([
                                "action":"$N右手一抬，勢做陰柔，無聲無息襲向$n，跟着左爪突然而出，以陽剛\n之力，左右合擊直取$n的喉嚨。",
                                "damage_type": "內傷",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(100),
                        ]);
                }
                else
                {
                        addn("neili", -80, me);
                        return ([
                                "action":"$N內力勃發，姿勢兇狠，眼露兇光，招招不離$n的要害部位，似乎要將$n生吞活剝。\n"
                                 "$N雙手連揚，連出陰招，不離鎖喉，撩陰。$n稍有疏忽不免死得慘酷無比。",
                                "damage_type": "抓傷",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(200),
                        ]);
                }
        }
        return ([
                "action"     : action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"抓傷":"內傷",
                "dodge"      : -35+random(20),
                "parry"      : 25+random(30),
                "force"      : 80+random(100),
        ]);
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("鎖喉功必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練鎖喉功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suohou-gong/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n鎖喉功："NOR"\n");
        write(@HELP

    鎖喉功為丐幫的武技。

        學習要求：
                混天氣功20級
                內力100
HELP
        );
        return 1;
}
