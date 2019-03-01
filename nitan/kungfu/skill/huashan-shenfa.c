// huashan-shenfa.c 華山身法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n一式"HIY"「巨鵬亮翅」"NOR"，兩臂鵬舉如翼，在剌剌風聲中，從$N頭頂橫躍而過。\n",
"$n一式"HIC"「風送紫霞」"NOR"，如一陣清風，舒緩地閃過了$N的凌厲攻勢。\n",
"$n一式"HIB"「燕回朝陽」"NOR"，輕盈地一躍，一轉眼間便繞到了$N的身後。\n",
"$n一式"HIY"「卻別蒼鬆」"NOR"，一轉身間，向後飄出近一丈遠\n",
"$n一式"HIM"「旭日初升」"NOR"，全身筆直，拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
"$n一式"HIY"「金雁橫空」"NOR"，身體如一只金雁般行雲流水地滑出丈余。\n",
"$n一式"HIW"「晚月朗星」"NOR"，雙腳點地，全身化為一道白影，急速繞著$N打了幾轉。\n",
"$n一式"GRN"「幻眼雲湮」"NOR"，身形陡地變得飄忽不定，令$N無法看清。\n",
"$n一式"HIM"「蒼龍盤嶺」"NOR"，宛若一條矯矢蒼龍，圍著$N急速地盤旋了幾圈。\n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<20 || query("neili", me)<4 )
                return notify_fail("你的體力太差了，不能練華山身法。\n");
        me->receive_damage("qi", 20);
        addn("neili", -4, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 20; }
int power_point(object me) { return 1.2; }

int help(object me)
{
        write(HIC"\n華山身法："NOR"\n");
        write(@HELP

    華山身法為華山劍宗輕功身法。

        學習要求：
          紫霞神功10級
HELP
        );
        return 1;
}
