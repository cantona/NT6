// qimen-wuxing 奇門五行
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int valid_enable(string usage) { return usage=="taoism"; }
int practice_skill(object me)
{
        return notify_fail("奇門五行能靠學(learn)來提高。\n");
}
int valid_learn(object me)
{
        if( (int)me->query_skill("taoism") < 10	)
                return notify_fail("你的道家修為還不夠高深，無法學習奇門五行。\n");
        if ((int)me->query_skill("mathematics", 1) < 200)
                return notify_fail("你的算術知識太差，無法理解奇門五行的奧妙。\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("qimen-wuxing", 1))
                return notify_fail("你的算術知識有限，無法理解更深奧的奇門五行。\n");

        return 1;
}

string conjure_magic_file(string spell)
{
        return __DIR__ + "qimen-wuxing/" + spell;
}
int help(object me)
{
        write(HIC"\n奇門五行："NOR"\n");
        write(@HELP


    是東海桃花島的獨門功夫。相傳桃花島雖然地處海外，人跡罕
至，但島上卻是家傳淵博，對奇門五行研究得很深。有了這門功夫，
再配上桃花島的佈陣箱就可以擺出奇門五行陣，把敵人困在陣內。

    array somebody  在佈陣箱的配合下，可以對某人佈陣，使其
身陷陣內。

    可以閲讀《易經》系列書籍提高。


        學習要求：
                不能同時修習左右互博之術
HELP
        );
        return 1;
}
