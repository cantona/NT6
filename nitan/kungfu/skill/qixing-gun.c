// quanzhen-jianfa 全真劍法

inherit SKILL;

mapping *action = ({
([      "action" : "$N貼地斜飛，一招「雁行斜擊」，尚未落地，$w已指向$n的後心",
        "force" : 120,
        "dodge" : 20,
        "damage" : 25,
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N小步連跳，左手劍訣，右手$w使一式「浪跡天涯」直攻$n的左肋",
        "force" : 140,
        "dodge" : 15,
        "damage" : 30,
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「花前月下」，模擬冰輪橫空，清光舖地之光景，自上而下搏擊",
        "force" : 170,
        "dodge" : 15,
        "damage" : 40,
        "lvl" : 9,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍柄提起，劍尖下指，一招「清飲小酌」，猶如提壺斟酒掃$n的下盤",
        "force" : 190,
        "dodge" : 10,
        "damage" : 50,
        "lvl" : 19,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使出「撫琴按簫」，$w提至唇邊，如同清音出簫，劍掌直出，劃向$n的$l",
        "force" : 240,
        "dodge" : 10,
        "damage" : 60,
        "lvl" : 29,
        "damage_type" : "刺傷"
]),
([      "action" : "$N$w直截進擊，自左而右，橫掃數尺，一式「橫行漠北」，迅疾逼向$n的肩頭",
        "force" : 280,
        "dodge" : 5,
        "damage" : 70,
        "lvl" : 39,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「舉案齊眉」，左手捏劍訣，躍步落地，右手$w斜刺$n的左腰",
        "force" : 300,
        "dodge" : 5,
        "damage" : 80,
        "lvl" : 59,
        "damage_type" : "刺傷"
]),
([      "action" : "$N左掌前揮，右手揚劍跟隨，一招「推窗望月」，身形前揚，往$n的$l殺至",
        "force" : 330,
        "dodge" : -5,
        "damage" : 90,
        "lvl" : 79,
        "damage_type" : "刺傷"
]),
([  "action" : "$N一招「分花拂柳」，$w似左實有右，似右實左，虛實莫辯，點向$n的腹部",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "刺傷"
]),
([  "action" : "$N一招「錦筆生花」，英姿勃發，$w舞出數點寒心，若梅桃盛開，點向$n的$l",
        "force" : 380,
        "dodge" : -5,
        "damage" : 115,
        "lvl" : 99,
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "club") || (usage == "parry"); } 



int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        return 1;
        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的內功火候不到。\n");
}

mapping query_action(object me, object weapon)
{
        int i, level;
            level   = (int) me->query_skill("quanzhen-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("jingli", me)<50 )
                return notify_fail("你的精力不夠練全真劍法。\n");
        addn("jingli", -30, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"quanzhen-jianfa/" + action;
}