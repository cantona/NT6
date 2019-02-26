// suohou-hand 鎖喉擒拿手

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int lvl_temp;
string *action_msg = ({
        "$N左手揚起，右手伸出，五指曲張，對着$n的頸部便抓",
        "只見一陣勁風直逼向前$N單臂伸出，手指直取$n的哽嗓咽喉",
        "$N左手一掠，將$n防守招數盡格在外門，右手疾探而出對$n的喉頭抓到",
        "$N身形急跳，早落到$n的身後，一雙冰冷的大手抓向$n的後頸",
        "$N雙臂彎出，柔若無骨，如兩條軟鞭一般，緊緊纏住$n的脖子不放",
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }
int valid_combine(string combo) { return combo=="lianhua-zhang"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("huntian-qigong", 1) < 20)
                return notify_fail("你的混天氣功火候不到。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鎖喉擒拿手必須空手。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練鎖喉擒拿手。\n");
        if( query("neili", me)<15 )
                return notify_fail("你的內力不夠練鎖喉擒拿手。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
        lvl_temp = random((int)me->query_skill("suohou-hand", 1));
        if( lvl_temp>100 && query("neili", me)>800 )
        {
                if (lvl_temp <= 150)
                {
                        addn("neili", -50, me);
                        return ([
                                "action":"$N右手一抬，勢做陰柔，無聲無息襲向$n，跟着左爪突然而出，以陽剛\n之力，左右合擊直取$n的喉嚨。",
                                "damage_type": "內傷",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(100),
                        ]);
                }
                else
                {
                        addn("neili", -80, me);
                        return ([
                                "action":"$N內力勃發，姿勢兇狠，眼露兇光，招招不離$n的要害部位，似乎要將$n生吞活剝。\n"
                                 "$N雙手連揚，連出陰招，不離鎖喉，撩陰。$n稍有疏忽不免死得慘酷無比。",
                                "damage_type": "抓傷",
                                "dodge": -35+random(20),
                                "parry": 25+random(30),
                                "force" : 80+random(200),
                        ]);
                }
        }
        return ([
                "action"     : action_msg[random(sizeof(action_msg))],
                "damage_type": random(2)?"抓傷":"內傷",
                "dodge"      : -35+random(20),
                "parry"      : 25+random(30),
                "force"      : 80+random(100),
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n鎖喉擒拿手："NOR"\n");
        write(@HELP

    鎖喉擒拿手為丐幫的武技。
    可與蓮花手互備。

        學習要求：
                混天氣功20級
                內力100
HELP
        );
        return 1;
}

