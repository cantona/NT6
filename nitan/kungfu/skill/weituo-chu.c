// This program is a part of NT MudLIB
// weituo-chu.c 韋陀杵

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([
        "action" : "$N躍在半空，一招"HIG"「仙鶴展翅入靈山」"NOR"，手中$w已化成無數棍影，令$n眼花繚亂，不知所措，連連倒退",
        "lvl"    : 0,
        "skill_name" : "仙鶴展翅入靈山"
]),
([
        "action" : "$N挺$w將$n的$W架住，順勢一招"HIC"「玉馬銜環拜仙宮」"NOR"，$w上下左右飛快攪動，身隨棍走，向$n壓了下來",
        "lvl"    : 40,
        "skill_name" : "玉馬銜環拜仙宮"
]),
([
        "action" : "$N一招"HIY"「鳴鹿踏蹄覓仙草」"NOR"，屈膝俯身，手中$w連點$n下盤，卻未等招數用老，猛的一提，向$n的胸腹間戳去",
        "lvl"    : 60,
        "skill_name" : "鳴鹿踏蹄覓仙草"
]),
([
        "action" : "$N突然滾到在地，$n錯愕間，一招"HIR"「金鯉躍水潛天池」"NOR"，竟從$n的襠下竄過，更不回頭，$w反手掃向$n的$l",
        "lvl"    : 80,
        "skill_name" : "金鯉躍水潛天池"
]),
([
        "action" : "$N一招"HIM"「靈猿獻果赴蓬萊」"NOR"，身形如電，繞着$n飛快奔跑，手中$w一招快似一招，剎那間向$n連打出十六棍",
        "lvl"    : 100,
        "skill_name" : "靈猿獻果赴蓬萊"
]),
([
        "action" : "$N大踏步上前，勁貫雙臂，手中$w大開大闔，呼呼風聲中一招"HIC"「飛鷹盤旋掃乾坤」"NOR"掃向$n的腰間",
        "lvl"    : 120,
        "skill_name" : "飛鷹盤旋掃乾坤"
]),
([
        "action" : "$N大喝一聲，一招"HIY"「天龍出水騰宇宙」"NOR"，$w脱手飛出，夾着勁風射向$n的前心，隨即搶到$n的身後，伸手又把$w抄在手中",
        "lvl"    : 130,
        "skill_name" : "天龍出水騰宇宙"
]),
([
        "action" : "$N雙目圓睜，口中默誦真言，一招"HIW"「白象捲雲憾天柱」"NOR"，$w似有千斤，緩緩舉起，又緩緩向$n的當頭砸落",
        "lvl"    : 150,
        "skill_name" : "白象捲雲憾天柱"
]),
});

int valid_enable(string usage) { return (usage=="club") || (usage=="parry"); }
int valid_learn(object me)
{
        mapping fam  = me->query("family");

        if (fam["family_name"] != "少林派" )
                return notify_fail("韋陀杵只能從少林派學到。\n");

        if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的內力不夠。\n");
        /*
        if ((int)me->query_skill("ranmu-daofa",1) > 1 || (int)me->query_skill("riyue-bian",1) > 1)
                return notify_fail("你如果有達摩老祖的修為，方可同時學習少林三絕技。\n");
        */
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
                query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練韋陀棍。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練韋陀棍。\n");
        me->receive_damage("qi", 60);
        if((int)me->query_skill("weituo-chu",1)> 200)
        {
                addn("neili", -20, me);
        }
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
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -5;
        int p_e2 = 10;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 150;
        int m_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("weituo-chu", 1);
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
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"weituo-chu/" + action;
}
int help(object me)
{
        write(HIC"\n韋陀杵："NOR"\n");
        write(@HELP

    韋陀杵是少林頂級棍法。
    韋陀杵、日月鞭法和燃木刀法並列為少林三絕技。
    三絕技不能同時修習。

        學習要求：
                易筋經150級
                站樁功150級
                少林醉棍150級
                內力修為1500
HELP
        );
        return 1;
}
