// ziyunyin.c 紫氳吟
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

#include <ansi.h>
void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_learn(object me)
{
        if( me->query_skill("zixia-shengong",1) < 30)
                return notify_fail(RANK_D->query_respect(me) + "，華山九功，紫霞第一，你學了多少？\n");
        if( me->query_skill("buddhism",1) > 1) 
                return notify_fail(RANK_D->query_respect(me)+"既參禪宗，如何能領會我華山以氣御萬物的道理？\n");
        if( (int)me->query_skill("taoism",1) > 1 )
                return notify_fail("你學了太上道祖之心法，如何能領會我華山以氣御萬物的道理？\n");
        if ((me->query_skill("poison",1) > 1))
                return notify_fail("哈哈！"+ RANK_D->query_respect(me)+"已經學了邪魔外道的毒技，怎麼領會我堂堂紫氳吟？\n");
        if ((me->query_skill("lamaism",1) > 1))
                return notify_fail("哈哈！"+ RANK_D->query_respect(me)+"已經學了密宗心法，即非我正派中人！\n");
        if (me->query_skill("ziyunyin", 1) >= 100)
                return notify_fail("限于資質，你對紫氳吟的理解也就到此為止了。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("紫氳吟只能靠學(learn)來提高。\n");
}

int help(object me)
{
        write(HIC"\n紫氳吟："NOR"\n");
        write(@HELP

    紫氳吟為華山心法，配合紫霞神功能增加精。
    可尋找紫氳譜閱讀。

        學習要求：
                紫霞神功30級
                與道家心法、禪宗心法、密宗心法和基本毒技不能兼學
HELP
        );
        return 1;
}
