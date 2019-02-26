// 北斗星由天樞、天旋、天璣、天權、玉衡、開陽、搖光這七顆星組成，運轉於北
// 極星周圍。其中，天樞至天權四星為魁，玉衡至搖光為榴。《史記·天官書》記
// 載“北斗七星，所謂璇璣玉衡，以齊七政。構攜龍角，衡段南鬥，魁枕參首”。

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N右手五指分開，微微一拂，一式「天樞指」拂向$n的膻中要穴",
        "force" : 100,
        "dodge" : 15,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "瘀傷",
        "skill_name" : "天樞指"
]),
([      "action": "$N側身掠向$n，一式「天旋指」，左手五指撥向$n的胸前大穴",
        "force" : 130,
        "dodge" : 20,
        "damage": 30,
        "lvl"   : 30,
        "damage_type" : "瘀傷",
        "skill_name" : "天旋指"
]),
([      "action": "$N使一式「天璣指」，左掌虛攻，並指斜前翻出，拍向$n的肩井穴",
        "force" : 170,
        "dodge" : 25,
        "damage": 40,
        "lvl"   : 60,
        "damage_type" : "內傷",
        "skill_name" : "天璣指"
]),
([      "action": "$N微微側身，右掌勾上，一式「天權指」，緩緩拂向$n的天突穴",
        "force" : 190,
        "dodge" : 25,
        "damage": 45,
        "lvl"   : 80,
        "damage_type" : "瘀傷",
        "skill_name" : "天權指"
]),
([      "action": "$N使一式「玉衡指」，身影不定地掠至$n身後，猛地拍向$n的大椎穴",
        "force" : 220,
        "dodge" : 30,
        "damage": 50,
        "lvl"   : 100,
        "damage_type" : "瘀傷",
        "skill_name" : "玉衡指"
]),
([      "action": "$N施出「開陽指」，雙手向外一撥，逼向$n的華蓋、璇璣、紫宮幾處大穴",
        "force" : 250,
        "dodge" : 35,
        "damage": 55,
        "lvl"   : 120,
        "damage_type" : "瘀傷",
        "skill_name" : "開陽指"
]),
([      "action": "$N一式「搖光指」，居高臨下，拂出一道勁力罩向$n的百會大穴",
        "force" : 280,
        "dodge" : 40,
        "damage": 65,
        "lvl"   : 140,
        "damage_type" : "內傷",
        "skill_name" : "搖光指"
]),
([      "action": "$N施展出「璇璣開破」，雙手疾拂，一環環的勁氣逼向$n的上中下各大要穴",
        "force" : 320,
        "dodge" : 45,
        "damage": 70,
        "lvl"   : 160,
        "damage_type" : "內傷",
        "skill_name" : "璇璣開破"
])
});

int valid_enable(string usage)
{
        return usage == "hand" ||  usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "haotian-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練七星分天手必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學七星分天手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練七星分天手。\n");

        if ((int)me->query_skill("hand", 1) < 80)
                return notify_fail("你的基本手法太差，無法學習七星分天手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qixing-shou", 1))
                return notify_fail("你基本手法火候不夠，無法領會更高深的七星分天手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qixing-shou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了，無法練七星分天手。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的體力太低了，無法練七星分天手。\n");

        me->receive_damage("qi", 80);
        addn("neili", -53, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qixing-shou/" + action;
}