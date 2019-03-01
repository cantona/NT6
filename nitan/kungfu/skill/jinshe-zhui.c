// jinshe-zhui.c 金蛇錐法
//last Modified by Sega by 3/18/2000
//算是暗器中的特殊吧,威力很大但易被還擊,而且難練.

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "name":                "千變萬化",
        "action":"$N雙手一晃，一招「千變萬化」，手中的$w幻出萬道金光，
如一條金龍般飛向$n的$l",
        "dodge":        -20,
        "force":        200,
        "damage":        300,
        "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
        "damage_type":  "刺傷"
]),
([        "name":                "奇詭莫測",
        "action":"$N右手一抖，一道金光冒出，只一剎那間，左手$w迅雷般越
過右手的$w，正是一招「奇詭莫測」，搶先飛向$n的$l",
        "dodge":        -30,
        "force":        300,
        "damage":        400,
        "post_action":  (: call_other, WEAPON_D, "throw_weapon" :),
        "damage_type":  "刺傷"
]),
});

int valid_enable(string usage) { return usage=="throwing" ; }
int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠，沒有辦法練金蛇錐法。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，沒有辦法練金蛇錐法。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("jinshe-zhui", 1))
                return notify_fail("你的基本暗器水平有限，無法領會更高深的金蛇錐法。\n");

        return 1;
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
int practice_skill(object me)
{
        object weapon;

/*
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "throwing" )
                return notify_fail("你使用的武器不對。\n");
*/
        if( query("qi", me)<30
         || query("neili", me)<500 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習金蛇錐法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -30, me);
//        write("你按著所學練了一遍金蛇錐法。\n");
        return 1;
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"jinshe-zhui/" + action;
}

int help(object me)
{
        write(HIC"\n金蛇錐法："NOR"\n");
        write(@HELP

    金蛇錐法載于「金蛇密笈」，乃金蛇郎君夏雪宜的獨門武功。
夏雪宜幼時全家不幸被溫家五老劫掠滅門，立志報仇。後于苗疆得
識五毒教教主之妹何紅藥，並得其助獲得五毒教的「三寶」──金
蛇劍、金蛇錐及藏寶圖，因而練成絕世武功。
    夏雪宜性情古怪，為人陰狠，武功便正如其人般詭異難測。江
湖上人人聞其名而為之色變，乃是出名的難纏人物。夏雪宜留下的
「金蛇密笈」載有他一身武功，即金蛇劍法、金蛇錐法和金蛇遊身
掌。

        學習要求：
                內力500
HELP
        );
        return 1;
}
