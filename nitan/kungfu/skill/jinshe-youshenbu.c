inherit SKILL;

string *dodge_msg = ({
    "$n身行如鬼魅般一晃，剎那間已遠去數丈之外，$N頓時撲了個空。\n",
    "$n的身行頓時變得如蛇一般柔軟，隨着$N的招式左右擺動，竟使得$N招招落空。\n",
    "$n如一縷青煙般繞着$N飛快旋轉，看得$N一陣頭暈眼花，急忙收招跳開。\n",
    "$n怪異的一笑，身行朦朧，$N的凌厲招式竟然透體而過，原來竟是一具幻影。\n",
});

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<50 )
        return notify_fail("你的體力太差了，不能練金蛇遊身步。\n");

    me->receive_damage("qi", 40);
    return 1;
}