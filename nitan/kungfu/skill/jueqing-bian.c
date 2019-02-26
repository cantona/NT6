// jueqing-bian.c  絕情鞭法

#include <ansi.h>

inherit SKILL;
#include <ansi.h>
#include <combat.h>
int sanwu
(object me, object victim, object weapon, int damage);

mapping *action = ({
([        "action":                "$N輕抖手腕，一招「青蛇吐芯」，手中$w抖得筆直，直向$n捲去",
        "force":                60,
        "dodge":                -30,
        "damage":                30,
        "lvl" : 0,
        "skill_name" : "青蛇吐芯",
        "damage_type":        "鞭傷"
]),
([        "action":                "$N身形一轉，一招「毒蠍反尾」，$w在空中轉了個圈，以怪異的角度劈向$n",
        "force":                120,
        "dodge":                -20,
        "damage":                40,
        "lvl" : 10,
        "skill_name" : "毒蠍反尾",
        "damage_type":        "鞭傷"
]),
([        "action":                "$N一抖長鞭，一招「黑蛛吐絲」，手中$w化做無數幻影，罩向$n",
        "force":                180,
        "dodge":                -30,
        "damage":                50,
        "lvl" : 20,
        "skill_name" : "黑蛛吐絲",
        "damage_type":        "鞭傷"
]),
([        "action":                "$N力貫鞭梢，一招「蟾蜍出洞」，手中$w忽左忽右，直劈向$n胸口",
        "force":                240,
        "dodge":                -10,
        "damage":                60,
        "lvl" : 30,
        "skill_name" : "蟾蜍出洞",
        "damage_type":        "鞭傷"
]),
([        "action":                "$N運氣於腕，一招「蜈蚣翻身」，手中$w轉起無數個圈圈，帶着一股陰風，直向$n撲去",
        "force":                300,
        "dodge":                -20,
        "damage":                80,
        "lvl" : 40,
        "skill_name" : "蜈蚣翻身",
        "damage_type":        "鞭傷"
])

});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if( (int)me->query_skill("wudu-xinfa") < 25 )
                return notify_fail("你的五毒心法太低，不能練絕情鞭法。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練絕情鞭法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
//        三無三不手
        mapping a_action;
        int i, level;
        string *sanwu_msg = 
        ({
                "$N一招"+WHT"「無孔不入」"+NOR"，$n身前身後都是$w的影子同時點$n全身各處大穴",
                "$N一招未絕，第二招"+WHT"「無所不至」"+NOR"以然打到，手中$w點向$n周身諸處偏門穴道",
                WHT"兩招掃過$N又是一招「無所不為」，$w迴旋飛至，專打$n周身柔弱之處"NOR,
        });
        level   = (int) me->query_skill("jueqing-bian", 1);

                if( query_temp("sanwu", me)>0 && query_temp("sanwu", me) <= 3 )
                {
                        return ([
                        "action":sanwu_msg[query_temp("sanwu", me)-1],
                        "dodge": -200,
                        "parry": -225,
                        "force": 400,
                        "damage": 100,
                        "damage_type": "鞭傷",
                        "post_action": (: sanwu :) ]);
                }

                for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                {
                        a_action = action[NewRandom(i, 20, level / 5)];
                        break;
                }
        a_action["force"] += level / 10;
        a_action["dodge"] -= level / 10;
        a_action["parry"] = level / 10;
        a_action["damage"] += level / 10;
        return a_action;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的精力不夠練絕情鞭法。\n");
        me->receive_damage("jingli", 25, "精力透支過度死了。");
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jueqing-bian/" + action;
}

int sanwu(object me, object victim, object weapon, int damage)
{
//        if( damage > 0 && me->query_temp("sanwu") ) 
//                me->delete_temp("sanwu");
}
mapping *query_skilldbase() {return action;}
