// lianhuan-mizongtui.c 連環迷蹤腿
// Vin 6/3/2001

inherit SKILL;

string *dodge_msg = ({
        "$n身形微微一晃，雙足連環踢出，將$N硬生生迫退。\n",
        "$n錯步上前，單足忽的一抬，將$N的攻勢全部擋回，只能自保。\n",
        "$n雙足輕輕點地，猛的拔地而起，躲開了$N的招式。\n",
});

mapping *action = ({
([      "action" : "$N雙手虛晃，左腳猛地飛起，一式「盪寇金湯」，腳尖晃動，踢向$n的$l",
        "force" : 80,
        "attack": 10,
        "dodge" : 45,
        "parry" : 45,
        "damage": 10,
        "lvl"   : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "盪寇金湯"
]),
([      "action" : "$N左腳頓地，別轉身來抽身欲走，只一剎那間一回身，右腳一式「幻影腿」，猛踹$n的$l",
        "force" : 100,
        "attack": 20,
        "dodge" : 50,
        "parry" : 50,
        "damage": 15,
        "lvl"   : 40,
        "damage_type" : "瘀傷",
        "skill_name"  : "幻影腿"
]),
([      "action" : "$N左手一掙，右腳飛一般踹出，既猛且準，一式「聚精匯積」，踢中的$n的胸口",
        "force" : 160,
        "attack": 30,
        "dodge" : 55,
        "parry" : 55,
        "damage": 18,
        "lvl"   : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "聚精匯積"
]),
([      "action" : "$N突然躍起，雙足連環圈轉，一式「無影無蹤」，足帶風塵，攻向$n的全身",
        "force" : 190,
        "attack": 35,
        "dodge" : 60,
        "parry" : 60,
        "damage": 20,
        "lvl"   : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "無影無蹤"
]),
([      "action" : "$N兩手護胸，雙腳交叉踢起，一式「雙龍開破」，腳腳不離$n的面門左右",
        "force" : 220,
        "attack": 35,
        "dodge" : 70,
        "parry" : 70,
        "damage": 25,
        "lvl"   : 140,
        "damage_type" : "瘀傷",
        "skill_name"  : "雙龍開破"
]),
([      "action" : "$N突然側身，卻步後退，一個前空翻，右腳自上而下一式「流星飛墜」，照$n的面門直劈下來",
        "force" : 260,
        "attack": 40,
        "dodge" : 90,
        "parry" : 90,
        "damage": 30,
        "lvl"   : 160,
        "damage_type" : "瘀傷",
        "skill_name"  : "流星飛墜"
]),
([      "action" : "$N使一式「無形定位」，全身突然飛速旋轉，雙足忽前忽後，迅猛無及踹向$n的胸口",
        "force" : 290,
        "attack": 40,
        "dodge" : 100,
        "parry" : 100,
        "damage": 30,
        "lvl"   : 180,
        "damage_type" : "瘀傷",
        "skill_name"  : "無形定位"
]),
([      "action" : "$N抽身躍起，開聲吐氣，大喝一聲，一式「連環迷蹤」，雙腳如旋風般踢向$n的$l",
        "force" : 340,
        "attack": 45,
        "dodge" : 115,
        "parry" : 115,
        "damage": 35,
        "lvl"   : 200,
        "damage_type" : "瘀傷",
        "skill_name"  : "連環迷蹤"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry" ||  usage=="dodge"; } 

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習連環迷蹤腿必須空手。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的內功火候不夠，無法學連環迷蹤腿。\n");

        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("你的基本輕功火候不夠，無法學連環迷蹤腿。\n");

        if ((int)me->query_skill("unarmed", 1) < 80)
                return notify_fail("你的基本拳腳火候不夠，無法學連環迷蹤腿。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練連環迷蹤腿。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("lianhuan-mizongtui", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的連環迷蹤腿。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("lianhuan-mizongtui", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的連環迷蹤腿。\n");

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
        int i, level;
        level = (int)me->query_skill("lianhuan-mizongtui", 1);
        for(i = sizeof(action); i > 0; i--)
            if(level > action[i-1]["lvl"])
                return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
               return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
               return notify_fail("你的內力不夠練連環迷蹤腿。\n");

        me->receive_damage("qi", 80);
        addn("neili", -60, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lianhuan-mizongtui/" + action;
}