// luohan-gun.c 
// modified by gladiator

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action":"$N一招「羅漢問路」，手中$w如羅漢長手，招招向$n的下盤點去",
        "force" : 120,
        "attack": 25,
        "dodge" : 5,
        "parry" : 30,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "羅漢問路",
        "damage_type":"挫傷"
]),
([      "action":"$N把$w平提胸口，一擰身，一招「羅漢翻身」，$w猛地撩向$n的頸部",
        "force" : 150,
        "attack": 37,
        "dodge" : 5,
        "parry" : 31,
        "damage": 15,
        "lvl"   : 40,
        "skill_name" : "羅漢翻身",
        "damage_type":"挫傷"
]),
([      "action":"$N一招「平地龍飛」，全身滴溜溜地在地上打個大轉，舉棍向$n的胸腹間戳去",
        "force" : 180,
        "attack": 42,
        "dodge" : 5,
        "parry" : 37,
        "damage": 20,
        "lvl"   : 80,
        "skill_name" : "平地龍飛",
        "damage_type":"挫傷"
]),
([      "action":"$N伏地一個滾翻，一招「伏虎聽風」，$w挾呼呼風聲迅猛掃向$n的足脛",
        "force" : 210,
        "attack": 43,
        "dodge" : 15,
        "parry" : 35,
        "damage": 25,
        "lvl"   : 100,
        "skill_name" : "伏虎聽風",
        "damage_type":"挫傷"
]),
([      "action":"$N一招「流星趕月」，身棍合一，棍端逼成一條直線，流星般向頂向$n的$l",
        "force" : 240,
        "attack": 49,
        "dodge" : 20,
        "parry" : 41,
        "damage": 30,
        "lvl"   : 120,
        "skill_name" : "流星趕月",
        "damage_type":"挫傷"
]),
([      "action":"$N雙手持棍劃了個天地大圈，一招「紅霞貫日」，一棍從圓心正中擊出，撞向$n的胸口",
        "force" : 270,
        "attack": 58,
        "dodge" : 20,
        "parry" : 45,
        "damage": 35,
        "lvl"   : 140,
        "skill_name" : "紅霞貫日",
        "damage_type":"挫傷"
]),
([      "action":"$N一招「投鞭斷流」，$w高舉，以雷霆萬鈞之勢對準$n的天靈當頭劈下",
        "force" : 300,
        "attack": 61,
        "dodge" : 25,
        "parry" : 52,
        "damage": 40,
        "lvl"   : 160,
        "skill_name" : "投鞭斷流",
        "damage_type":"挫傷"
]),
([      "action":"$N潛運真力，一招「蒼龍歸海」，$w頓時長了數丈，矯龍般直射$n的胸口",
        "force" : 320,
        "attack": 63,
        "dodge" : 30,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 180,
        "skill_name" : "蒼龍歸海",
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");
        
        if ((int)me->query_skill("club", 1) < 100)
                return notify_fail("你的基本棍法水平還不足以學習十八羅漢棍法。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("luohan-gun", 1))
                return notify_fail("你的基本棍法水平有限，無法領會更高深的十八羅漢棍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("luohan-gun", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練十八羅漢棍。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的體力不夠練十八羅漢棍。\n");

        me->receive_damage("qi", 62);
        addn("neili", -61, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luohan-gun/" + action;
}