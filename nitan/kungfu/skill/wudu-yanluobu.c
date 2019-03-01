// wudu-yanluobu 五毒煙蘿步
// Last Modified by sir on 10.18.2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
HIB"$n不慌不忙，一式「江水橫流」，身行倏的向一旁平移數尺，堪堪躲過了$N的功勢。\n"NOR,
HIB"$n身行如鬼魅般一晃，剎那間已遠去數丈之外，$N頓時撲了個空。\n"NOR,
BLU"$n身行忽的加快，如一縷青煙般繞著$N飛快旋轉，看得$N一陣頭暈眼花，急忙收招跳開。\n"NOR,
BLU"$n怪異的一笑，身行忽的變得朦朧不清，$N的凌厲招式竟然透體而過，原來竟是一具幻影。\n"NOR,
BLU"$n的身行頓時變得如蛇一般柔軟，隨著$N的招式左右擺動，竟使得$N招招落空。\n"NOR,
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me) { return 1; } 

int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("你的體力太差了，不能練五毒煙蘿步。\n");
        me->receive_damage("qi", 10);
        addn("neili", -2, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.1; }

string perform_action_file(string action)
{
      return __DIR__"wudu-yanluobu/" + action;
}

int help(object me)
{
        write(HIC"\n五毒煙蘿步："NOR"\n");
        write(@HELP

    五毒教祖師模仿毒蟲動作而創立的一門輕功，是五毒教本門內
功。

        學習要求：
           五毒神功10
HELP
        );
        return 1;
}
