// 潑墨披麻刀法

inherit SKILL;

mapping *action = ({
        ([  "action":       "$N使一招「白虹貫日」，手中$w輕飄飄地向$n的$l斬去！",
                "damage":        100,
                "damage_type":        "割傷"
        ]),
        ([  "action":       "$N金刃劈風，$w隨著一招「騰蛟起風」由下而上撩往$n的$l",
                "damage":        120,
                "damage_type":        "割傷"
        ]),
        ([  "action":       "$N身形一轉，一招「春風楊柳」$w刀光不定，斬向$n的$l",
                "damage":        140,
                "damage_type":        "割傷"
        ]),
        ([  "action":       "$N舞動$w，一招「心馳神遙」迅捷無倫地劈向$n的$l",
                "damage":        160,
                "damage_type":        "劃傷",
        ]),
        ([  "action":       "$N手中$w一晃，一招「青山依舊」往$n的$l斜斜砍出一刀",
                "damage":        180,
                "damage_type":        "割傷",
        ]),
        ([  "action":       "$N提刀過肩，蓄勁發力，一招「玉龍倒懸」直劈$n$l",
                "damage":        200,
                "damage_type":        "劈傷",
        ]),
        ([  "action":       "$N移步側身，使一招「漫山遍野」刀光霍霍斬向$n的$l",
                "damage":        250,
                "damage_type":        "劃傷",
        ]),
});

int valid_learn(object me)
{
        if(me->query_skill("xuantian-quan",1)<20)
                return notify_fail("你的「玄天拳法」不夠嫻熟。\n");
        if(me->query_skill("xuantian-neigong",1)<20)
        return notify_fail("你的「玄天內功」功力不夠。\n");
        if(me->query("max_force")<50)
        return notify_fail("你的內力修為不夠。\n");
        return 1;
}

int valid_enable(string usage)
{
        return (usage=="blade") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
        ||        (string)weapon->query("skill_type") != "blade" )
                return notify_fail("你必須先找一把刀，才能練刀法。\n");

        if( (int)me->query("kee") < 40 )
                return notify_fail("你的體力不夠練這門刀法，還是先休息休息吧。\n");
        me->receive_damage("kee", 40);
        return 1;
}

string perform_action_file(string action)
{
return "/daemon/class/meizhuang/pomopima-dao/"+action;
}
int power_point()        {        return 1.25;        }
