// /kungfu/skill/qingshen-fa
// by dubei
// 如來輕身法

inherit SKILL;

string *dodge_msg = ({
           "$n使出一招「輕身似空」，身體陡轉徐徐向上飄去。\n",
           "$n使出一招「明空如鏡」，雙足猛然向上彈起，躍至半空之中。\n",
           "$n使出一招「蓮空」，身形一變，滑至$N身後。\n",
            "$n大吼一聲，使出一招「大安空」，從$N頭頂越過。\n",
            "$n使出一招「佛空」，如輕鴻般飄去，瞬間又閃至$N面前。\n",
             "$n使出一招「金剛空」，頓時$N周圍都是$n的身影。\n",
 });


 
int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("jingli", me)<50 )
                return notify_fail("你的體力太差了，不能練如來輕身法。\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{       
               return __DIR__"qingshen-fa/" + action;
}