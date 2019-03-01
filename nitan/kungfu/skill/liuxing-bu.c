// Updated by Lonely
// liuxingbu 流星步

inherit SKILL;

string *dodge_msg = ({
        "只見$n一式「銀鞍照白馬」，借力轉力身子騰空而起，躲過了$N這一招。\n",
          "$n身子斜飛而起，一式「颯沓如流星」避過了$N這一招。\n",
          "$n一式「千裡不留行」避過$N的攻勢，腳在$N的身上一點，飄出數丈。\n",
          "$n一轉身，雙掌往後拍出，借力一招「事了拂衣去」躲開$N這一招。\n", 
          "$n身子往地下一躺，腳一撐一招「深藏身與名」身子貼地滑出躲開$N的這一招。\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("jingli", me)<40 )
                return notify_fail("你的精力太差了，不能練俠客遊。\n");
        me->receive_damage("jingli", 30);
        return 1;
}