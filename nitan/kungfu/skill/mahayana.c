// mahayana.c 大乘涅磐功
//Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( query("shen", me)<0 )
                return notify_fail("你的邪氣太重，無法修煉大乘涅磐功。\n");

        return 1;
}

void skill_improved(object me)
{
        if ((int)me->query_skill("mahayana", 1) == 120 &&
            !query("sl_gift/mhyn", me) && query("gender", me) != "男性" )
        {
                addn("dex", 1, me);
                set("sl_gift/mhyn", 1, me);
                tell_object(me, HIM "\n你的大乘涅磐功學有所成，提高了你的身法。\n" NOR);
        }
}

int help(object me)
{
        write(HIC"\n大乘涅磐功："NOR"\n");
        write(@HELP

    峨嵋派素不喜與人爭鬥，弟子門人常常閉門修煉以增長人體潛
能，其有效程度乃取決於佛法修為（即大乘涅磐功的等級）。打坐
靜修可在峨嵋禪房使用命令jingzuo。請help jingzuo。

        學習要求：
                相應的臨濟十二莊
                不能學禪宗心法外的其他宗教心法
HELP
        );
        return 1;
}
