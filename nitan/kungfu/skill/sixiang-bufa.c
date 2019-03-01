inherit SKILL;

string *dodge_msg = ({
    "只見$n一招「少陰步」，身體向上筆直地縱起丈余，躲過了$N這一招。\n",
    "$n一個「乾兌步」，向後縱出數丈之遠，避開了$N的凌厲攻勢。\n",
    "$n使出「離震步」，向一旁飄然縱出，輕輕著地。\n"
    "但是$n身形飄忽，使出「少陽步」，輕輕一縱，早已避開。\n",
    "$n身隨意轉「太陰步」，倏地往一旁挪開了三尺，避過了這一招。\n",
    "可是$n側身一讓，一個「巽坎步」，$N這一招撲了個空。\n",
});

int valid_enable(string usage)
{
        return (usage == "dodge") ||
               (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("sixiang-bufa", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 10;
        if (lvl < 150) return 20;
        if (lvl < 200) return 30;
        if (lvl < 250) return 40;
        return 50;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太差了，不能練四象步法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力太差了，不能練習四象步法。\n");

        me->receive_damage("qi", 58);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"sixiang-bufa/" + action;
}