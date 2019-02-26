// shenxing-baibian.c 神行百變
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"HIC"「行雲流水」"NOR"，身不傾，腳不移，身體如行雲流水般直滑出丈餘。\n",
"$n一式"BLU"「潛音夜行」"NOR"，忽然一彎腰，全身貼地而行，頓時閃過了$N的凌厲攻勢。\n",
"$n一式"HIW"「移步換形」"NOR"，足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
"$n一式"MAG"「分身化影」"NOR"，一轉身間，四面八方飄動着無數個$n的身影，令$N手足無措。\n",
"$n一式"HIB"「凌波微步」"NOR"，左踏巽，右轉乾，身行一晃，便到幾丈遠的地方。\n",
"$n一式"HIM"「更上層樓」"NOR"，身在空中，左腳在右足上一點，從$N頭頂騰空而過。\n",
"$n一式"HIW"「仙子出水」"NOR"，長袖一拂，全身化為一道白影，幽幽地從$N頭頂飄落。\n",
"$n一式"HIG"「峯迴路轉」"NOR"，身體如陀螺般急轉，登時一股氣流湧出，令$N難以動彈。\n",
"$n一式"GRN"「臨行秋波」"NOR"，身行倏的從$N的眼前直繞到身後，$N瞪大了兩眼，不明所以。\n",
"$n一式"HIY"「浪子回頭」"NOR"，身行倏的從$N的眼前飄過，長髮一甩，瀟灑之極。\n",
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        if( query("kar", me)<25
              || query("int", me)<21 )
                return notify_fail("看來你無緣領悟神行百變。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 || query("neili", me)<8 )
                return notify_fail("你的體力太差了，不能練神行百變。\n");
        me->receive_damage("qi", 40);
        addn("neili", -8, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) {
        if( query("skybook/luding/dubi", me))return 1.4;
        else        return 0.9; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("shenxing-baibian", 1) < 50 ||
            ! living(me))
                return;

        mp = ob->query_skill("martial-cognize", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("shenxing-baibian", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                 result += (["msg" : HIC "$n" HIC "施展神行百變，神光離合，一轉身間，四面八方飄動着無數個$n的身影，\n"
                                    HIC "$N" HIC "手足無措，頭腦發昏，只覺得四面都是$n的身影，所發招數盡數落空。\n" NOR]);
                return result;
        }
}

int help(object me)
{
        write(HIC"\n神行百變："NOR"\n");
        write(@HELP

    神行百變是鐵劍門木桑道長所傳下來的輕功絕技，是逃命的高招。

        學習要求：
           一定的機緣向獨臂神尼學習
HELP
        );
        return 1;
}
