// mantian-xing.c 滿天星
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *dodge_msg = ({
        "$n左一點右一晃，隨即回到原地，輕巧地躲過了$N這一招。\n",
        "$n騰身躍起一個空翻，並順勢閃到一邊。\n",
        "$n輕輕往旁邊一縱，就已離$N有了相當的距離，$N這一招自然失效。\n",
        "$n揉身而上，輕靈地躍過$N，閃到了$N的背後。\n",
        "$n身形急閃，斜向前一步，竟然已經躲開了$N的這一招。\n",
        "$N眼前一花，卻見$n竟然已離自己有數丈之遠，卻沒見$n如何躲過自己的攻擊的。\n",
        "$N一個不留神，$n已沒了蹤影。$N急轉身，卻見$n在那兒向自己招手。\n",
        "$N一招攻出，$n已然不見，$N茫然四顧，卻不見$n的影子！\n",
});

mapping *action = ({
([        "action" : "$N輕身而退，一招『初露星芒』，手中$w化作一點寒芒射向$n",
        "damage": 30,
        "dodge" : 20,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 0,
        "skill_name" : "初露星芒"
]),
([        "action" : "$N右手微向前一伸，使出『乍見星辰』，手裡$w徑直射向$n的雙眼",
        "damage": 40,
        "dodge" : 15,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 9,
        "skill_name" : "乍見星辰"
]),
([        "action" : "$N一聲輕嘯，施展出『寒夜孤星』，身形微動，手中$w竟然向上飛\n起繞了個圈，隨而迅速襲向$n的腰間",
        "damage": 50,
        "dodge" : 10,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 18,
        "skill_name" : "寒夜孤星"
]),
([        "action" : "$N使一招『星光閃爍』，突然縱身向後一個翻滾，就在快落地的一瞬
間，$n陡然發現幾點寒光閃爍不定地襲向自己",
        "damage": 55,
        "dodge" : 25,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "紮傷",
        "lvl" : 27,
        "skill_name" : "星光閃爍"
]),
([        "action" : "$N右手一揮，一招『星芒不定』，$n明明看見$N手裡的$w已射向自己
的胸前大穴，到了近處卻突然轉攻向自己的後心",
        "damage": 60,
        "dodge" : 20,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 36,
        "skill_name" : "星芒不定"
]),
([        "action" : "$N不急不緩地一矮身，使出『墜落之星』，手中$w平直地射向$n的嚥
喉，卻又加上暗勁使之中途改向，射向$n的下盤",
        "damage": 70,
        "dodge" : 30,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 45,
        "skill_name" : "墜落之星"
]),
([        "action" : "$N騰身一躍而起，施展出『黎明之星』，手裡的$w從上往下筆直地射
向$n的頭部",
        "damage": 85,
        "dodge" : 30,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 54,
        "skill_name" : "黎明之星"
]),
([        "action" : "$N原地一個急轉身，隨即雙手一拂，$w就飄飄忽忽地飛向$n，原來這
招是『星辰遊離』",
        "damage": 110,
        "dodge" : 45,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 63,
        "skill_name" : "星辰遊離"
]),
([        "action" : "$N使出一招『星光頓滅』，前腳一跺，隨即翻身而起，手中$w不帶絲
毫風聲卻又迅速無比地射向$n的前胸",
        "damage": 190,
        "dodge" : 40,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 72,
        "skill_name" : "星光頓滅"
]),
([        "action" : "$N突然騰身向後急退，使出『星空炸雷』，雙手向前一推，手裡$w就
隱隱帶著雷聲疾射向$n",
        "damage": 240,
        "dodge" : 45,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 81,
        "skill_name" : "星空炸雷"
]),
([        "action" : "$N施展出『"+HIW"星劃長空"NOR+"』，原地側身飛起，右手微微向前一洒，手中$w
幻作一點寒光呈圓弧形射向$n",
        "damage": 260,
        "dodge" : 50,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 90,
        "skill_name" : "星劃長空"
]),
([        "action" : "$N微微凝神，使出『"+HIY"星光萬丈"NOR+"』，身影飄忽不定，$n頓覺十分刺眼，卻
見$N手裡的$w已挾著地上的沙石以及周圍的樹頁攻向自己",
        "damage": 190,
        "dodge" : 55,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 99,
        "skill_name" : "星光萬丈"
]),
([        "action" : "$N忽然輕嘆一聲，轉身而行，$n正遲疑間，卻見眼前已盡是$w的影子，
眼看無處可躲了！只怕這招就是『"+HIC"滿天星雨"NOR+"』了，$n不由大驚失色",
        "damage": 220,
        "dodge" : 70,
        "post_action": (: call_other, "/adm/daemons/weapond", "throw_weapon" :),
        "damage_type": "刺傷",
        "lvl" : 110,
        "skill_name" : "滿天星雨"
])
});

int valid_enable(string usage)
{
        return usage=="throwing" || usage=="parry" || usage=="dodge";
}
int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功心法火候不夠，無法學滿天星。\n");

        if ((int)me->query_skill("dodge") < 60)
                return notify_fail("你的輕功火候不夠，無法領悟滿天星。\n");

        if ((int)me->query_dex() < 25)
                return notify_fail("你的身法不夠靈巧，無法領悟滿天星。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("mantian-xing", 1))
                return notify_fail("你的基本暗器水平有限，難以領會更高深的滿天星。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練滿天星。\n");

        me->receive_damage("qi", 45);
        addn("neili", -35, me);
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
        level = (int)me->query_skill("mantian-xing", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"mantian-xing/" + action;
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1; }

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("mantian-xing",1)) > 50)
        {
                victim->apply_condition("anqi_poison", random(2) + 1 + victim->query_condition("anqi_poison"));
        }
}
int help(object me)
{
        write(HIC"\n滿天星："NOR"\n");
        write(@HELP

    鐵膽莊周仲英的成名絕技。

        學習要求：
                基本內法20級
                基本輕功20級
                後天身法25
HELP
        );
        return 1;
}
