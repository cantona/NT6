// king-of-dragon.c 帝王神功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }
string river_go_msg() {return HIW"$N微微一笑，信指召來一朵祥雲。緊接著$N飛身而上，白雲飄飄，往對岸而去。\n";}
string river_come_msg() {return HIW"只見$N身著黃金戰甲，腳踏七色祥雲，橫渡水面而來。\n";}

string *dodge_msg = ({
        HIY "$n端坐微笑，忽而臉現莊嚴之色，$N立刻匍匐在地，虔誠膜拜。\n" NOR ,
        HIY "$n舉手輕擺，$N立刻頭暈腦漲，一頭栽倒在地。\n" NOR ,
});

mapping *action = ({
([        "action": HIR "$N拈花微笑，周身湧起一片祥雲罩向$n" NOR ,
        "force" : 0,
        "dodge" : 0,
        "damage": 0,
        "lvl" : 0,
        "skill_name" : "君臨天下",
        "damage_type": "聖光之沐"
]),
});

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "dodge" || usage == "unarmed" || usage == "parry" || usage == "blade" || usage == "whip" || usage == "force" || usage == "claw" || usage == "spear" || usage == "dagger" || usage == "finger" || usage == "staff" ;
}

string query_skill_name(int level)
{
        int i;
        return action[0]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int i, level;
        return action[0];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[0];
}

int valid_learn(object me)
{        
        if ( ! wizardp(me))
        return notify_fail("﹝帝王神功﹞神功只能由巫師學習。\n");
}

string exert_function_file(string func)
{
        return __DIR__"king-of-dragon/" + func;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if ( ! userp (victim)) if ( living (victim)) victim -> unconcious () ;
}

int help(object me)
{
        write(HIC"\n帝王神功："NOR"\n");
        write(@HELP

    巫師內功。

        學習要求：
                巫師
HELP
        );
        return 1;
}
