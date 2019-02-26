#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這是商家堡的練武場，空闊的場地上鋪滿了細細的黃土，正
好適合演武。四面有幾個商家堡的弟子正在練武。練武場的中心
豎着幾根木樁(muzhuang)，周圍還挖有幾個沙坑(shakeng)。
LONG);
        set("item_desc", ([
                "shakeng"  : WHT "沙坑裏有些家將在練習輕功，你也可"
                             "以跳(tiao)下去試試。\n" NOR,
                "muzhuang" : WHT "幾根木樁上有不少擊打(jida)過的痕"
                             "跡。\n" NOR,
        ]));

        set("exits", ([
                "west"  : __DIR__"shang_qgc",
        ]));
	set("coor/x", -6740);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_jida", "jida");
        add_action("do_tiao", "tiao");
}

int do_jida(string arg)
{
        object me;
        object weapon;
        me = this_player();

        if (! living(me) || arg != "muzhuang")
                return notify_fail("你要擊打什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你操起手中兵器向木樁砍去，砍了半天發現毫無成效。\n");

        if ((int)me->query_skill("bagua-quan", 1) < 30
           || (int)me->query_skill("bagua-zhang", 1) < 30)
                return notify_fail("你擊打了半天，似乎沒什麼效果，可能是八卦拳掌等級太"
                                   "低的緣故。\n");

        if ((int)me->query_skill("bagua-quan", 1) >= 120
           && (int)me->query_skill("bagua-zhang", 1) >= 120)
                return notify_fail("你對着木樁擊打了一會兒，發現這裏已經不能再提高什麼"
                                   "了。\n");

        if( query("qi", me)<40 )
                return notify_fail("你現在累得胳膊都抬不起來了，還是先休息一會兒吧！\n");

        me->receive_damage("qi", 30);

        if (me->can_improve_skill("bagua-zhang")
           && (int)me->query_skill("bagua-zhang", 1) < 120)
                me->improve_skill("bagua-zhang",query("con", me)*2);

        if (me->can_improve_skill("bagua-quan")
           && (int)me->query_skill("bagua-quan", 1) < 120)
                me->improve_skill("bagua-quan",query("con", me)*2);

        me->start_busy(random(2));
        message_vision(WHT "\n$N" WHT "站穩馬步，一掌一拳對着木樁打了起來。\n" NOR, me);
        write(HIC "你在擊打過程中領悟了不少「八卦拳法」及「八卦掌法」的竅門。\n" NOR);
        return 1;
}

int do_tiao(string arg)
{
        object me;
        object weapon;
        me = this_player();

        if (! living(me) || arg != "shakeng")
                return notify_fail("你要擊打什麼？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙着呢。\n");

        if ((int)me->query_skill("dodge", 1) < 30
           || (int)me->query_skill("bagua-bu", 1) < 30)
                return notify_fail("你憋足氣朝着沙坑跳去，結果一跤重重地摔在了坑中。\n");

        if ((int)me->query_skill("dodge", 1) >= 120
           && (int)me->query_skill("bagua-bu", 1) >= 120)
                return notify_fail("你在沙坑周圍跳了一會兒，發現在這裏練習已經沒什麼用了。\n");

        if( query("qi", me)<40 )
                return notify_fail("你現在累得腳都抬不起來了，還是先休息一會兒吧！\n");

        me->receive_damage("qi", 30);

        if (me->can_improve_skill("dodge")
           && (int)me->query_skill("dodge", 1) < 120)
                me->improve_skill("dodge",query("con", me)*2);

        if (me->can_improve_skill("bagua-bu")
           && (int)me->query_skill("bagua-bu", 1) < 120)
                me->improve_skill("bagua-bu",query("con", me)*2);

        me->start_busy(random(2));
        message_vision(WHT "\n$N" WHT "深吸一口氣，“颼”的一聲跳過了沙坑，接着翻身一縱"
                       "又跳了回來。\n" NOR, me);
        write(HIC "你對「八卦步法」及「基本輕功」有了新的理解。\n" NOR);
        return 1;
}