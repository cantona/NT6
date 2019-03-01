// baiyun-xinfa.c 白雲心法
// Last Modify by sir 5/17/2001

#include <ansi.h>;
#include "force.h";
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }
int valid_enable(string usage) { return usage == "force"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point() { return 1; }

int valid_learn(object me)
{
        int i,nb,ny,ns;

        nb = (int)me->query_skill("buddhism", 1);
        ny = (int)me->query_skill("baiyun-xinfa", 1);
        ns=query("guilty", me);

        if( query("couple/couple_id", me) )
                return notify_fail("你塵緣未了，無法再學習白雲心法！\n");
        if( query("gender", me) != "女性" )
                return notify_fail("白雲心法只適合女性修練。\n");
        if( query("sex/times", me) )
                return notify_fail("你非處女之身，無法修習白雲心法！\n");
        if( (query("class", me) != "bonze") && i>29 )
                return notify_fail("你不是尼姑，學不了高深的白雲心法。\n");
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("你的基本內功火候還不夠。\n");

        if ( nb < 100 && nb <= ny )
                return notify_fail("你的禪宗心法修為不夠，無法領會更高深的白雲心法。\n");
        if ( ns > 0 )
                return notify_fail("你屢犯僧家數戒，無法領會更高深的白雲心法。\n");
        return valid_public(me);

}

int practice_skill(object me)
{
        return notify_fail("白雲心法只能用學(learn)的來增加熟練度。\n");
}
string exert_function_file(string func)
{
        return __DIR__"baiyun-xinfa/" + func;
}

int help(object me)
{
        write(HIC"\n白雲心法："NOR"\n");
        write(@HELP

  恆山派內功

        學習要求：
                基本內功10級
                處女純陰之體
HELP
        );
        return 1;
}
