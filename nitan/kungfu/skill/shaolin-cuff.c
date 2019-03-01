// Last Modified by winder on May. 29 2001
// shaolin-cuff.c - 少林南拳 南少林的入門空手功夫 與少林彈腿互備

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
 "$N一式『馬步雙插掌』，左腳向左橫跨一步，雙腿半蹲馬步，雙拳化掌用力前插",
 "$N一式『馬步沉橋』，馬步不動，雙手變掌，屈膝沉腕，使勁下壓",
 "$N右腳向左前一步，左腳繞過右腳，身體轉動不停，一式『騎龍步右踢腿』，向$n踢去",
 "$N身體左轉，右腳向左腳右跨一步，一式『馬步劈掌』，右拳化掌，右臂由曲變伸，向下斜劈",
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="shaolin-leg"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練少林南拳必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 1)
                return notify_fail("你的站樁功火候不夠，無法學少林南拳。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習少林南拳。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練少林南拳。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        return 1;
}
mapping query_action(object me, object weapon)
{
        return ([
                "action" : msg[random(sizeof(msg))],
                "dodge"  : 35+random(25),
                "parry"  : -20+random(15),
                "force"  : 70+random(150),
                "damage_type" : random(2)?"內傷":"瘀傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n少林南拳："NOR"\n");
        write(@HELP

    南拳是南少林入門拳法，多短打近攻，動作迅疾剛猛。強調站
樁，講究“四法一勁（身法、步法、手法、腿法和勁力）”，所謂
“步到身到手到，方為上手道”。

        學習要求：
                站樁功
HELP
        );
        return 1;
}
