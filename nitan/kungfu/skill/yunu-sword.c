// yunu-sword.c 玉女金針十三劍

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "穿針引線",
        "action":  "$N使一招"HIM"「穿針引線」"NOR"，腳踏中宮，手中$w直指$n$l",
        "lvl" : 0
]),
([        "skill_name" : "天衣無縫",
        "action":  "$N劍隨身轉，一招"HIB"「天衣無縫」"NOR"，撒出一片劍影，罩向$n的$l",
        "lvl" : 10
]),
([        "skill_name" : "夜繡鴛鴦",
        "action":  "$N舞動$w，使出一招"HIG"「夜繡鴛鴦」"NOR"劍光忽左忽右，閃爍不定，直刺$n的$l",
        "lvl" : 20
]),
([        "skill_name" : "織女穿梭",
        "action":  "$N一聲嬌喝，祭出"HIW"「織女穿梭」"NOR"，手中$w化為一道弧光，射向$n的$l",
        "lvl" : 30
]),
([        "skill_name" :  "小鳥依人",
        "action":  "$N忽然蹂身直上，一招"HIR"「小鳥依人」"NOR"，手中$w自下往上刺向$n的$l",
        "lvl" : 40
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;

        if( query("gender", me) != "女性" )
                return notify_fail("玉女金針十三劍是隻有女子才能練的武功。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太差，沒有辦法練玉女金針十三劍。\n") ;

        if( (int)me->query_skill("force") < 30 )
                return notify_fail("你的內功火候不夠，沒有辦法練玉女金針十三劍。\n") ;

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<35 || query("neili", me)<15 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習玉女金針十三劍。\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
//        write("你按著所學練了一遍玉女金針十三劍。\n");
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 15;
        int d_e2 = 40;
        int p_e1 = -10;
        int p_e2 = 5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 80;
        int m_e2 = 170;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yunu-sword", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "劈傷" : "刺傷",
        ]);
}
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string action)
{
        return __DIR__"yunu-sword/" + action;
}
int help(object me)
{
        write(HIC"\n玉女金針十三劍："NOR"\n");
        write(@HELP

    玉女金針十三劍是嶽夫人甯中則傳給女弟子的華山派劍法。

        學習要求：
                女性
                紫霞神功
                內力50
HELP
        );
        return 1;
}
