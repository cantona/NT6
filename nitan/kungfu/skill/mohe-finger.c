// Last Modified by Winder on May. 29 2001
// mohe-finger.c 摩訶指 和散花掌互備 截至佛經中“以慈度心，摩訶無量”一句。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N左掌一擺，護在胸前，接着右手食指畫出一個"HIB"「以」"NOR"字，輕輕點向$n$l",
        "lvl"   : 0,
        "skill_name" : "以"
]),
([        "action" : "$N左手食指緩緩畫了個"HIM"「慈」"NOR"字，跟着手指微曲，以字為中心，對着$n一彈",
        "lvl"   : 20,
        "skill_name" : "慈"
]),
([        "action" : "$N雙掌合十，身體微欠，雙指畫一"HIG"「度」"NOR"字，那撇捺兩畫有如兩條柳枝般，撫向$n$l",
        "lvl"   : 30,
        "skill_name" : "度"
]),
([        "action" : "$N雙手小指向$n揮動，連點三點，接着雙指併攏，一招斜劃，拼成了一個"HIR"「心」"NOR"字",
        "lvl"   : 50,
        "skill_name" : "心"
]),
([        "action" : "$N連連出招，幻出漫天指影，彷彿間竟然形成了一個"HIC"「摩」"NOR"字，照着$n激射而去，越來越快",
        "lvl"   : 60,
        "skill_name" : "摩"
]),
([        "action" : "$N右手食指伸出，在空中寫出個"HIW"「訶」"NOR"字來，形如狂草，向着$n最後一提時竟飛射出一道青氣",
        "lvl"   : 70,
        "skill_name" : "訶"
]),
([        "action" : "只見$N手指橫豎連劃，將指力在空中凝結不散，形成一個"CYN"「無」"NOR"字，對着$n當胸壓下",
        "lvl"   : 80,
        "skill_name" : "無"
]),
([        "action" : "$N雙拳併攏，夾出一個"HIY"「量」"NOR"字來，合力擊向$n，突然下半招一變，右手一指破空擊出",
        "lvl"   : 100,
        "skill_name" : "量"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo){ return combo=="sanhua-strike"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練摩訶指必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 30)
                return notify_fail("你的站樁功火候不夠，無法學摩訶指。\n");
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練摩訶指。\n");
        if (me->query_skill("weituo-strike", 1) < 30)
                return notify_fail("你的韋陀掌火候不夠，無法學摩訶指。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的精力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練摩訶指。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
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
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 100;
        int f_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("mohe-finger", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
         return __DIR__"mohe-finger/" + action;
}

int help(object me)
{
        write(HIC"\n摩訶指："NOR"\n");
        write(@HELP

    摩訶指是南少林入門指法，和散花掌互備。出自佛經中“以慈度心，摩訶無量”。

        學習要求：
                站樁功30級
                韋陀掌30級
                內力修為200
HELP
        );
        return 1;
}
