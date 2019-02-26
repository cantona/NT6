#include <ansi.h>; 
inherit ROOM;

void create()
{
        set("short", "獨木橋");
        set("long", @LONG
這是一條寬約七寸的獨木橋(bridge)，天風凜冽，吹的人
衣襟頭髮齊飛，只要一不留神，稍一失足，立刻便要粉身碎骨。
兩崖相隔，約有五十餘丈，往下看，峭壁如刀削，雲卷霧湧深
不見底，投塊石子下去，也聽不到回聲！
LONG);
        set("exits", ([ 
                "north" : __DIR__"xiaojing1",
        ]));
        set("item_desc",([
                "bridge" : YEL "這是一條寬約七寸的獨木橋，看來只"
                           "能走(zou)過一人。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_zou", "zou");
}

int do_zou(string arg)
{
        object me = this_player(), room;

        if (! arg || arg != "bridge")
                return notify_fail("你要走什麼？\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail(HIY "\n你戰戰兢兢地向前邁出兩"
                                   "步，可突然間穀風刮過，危橋一"
                                   "陣狂\n顫，嚇得你趕忙收回了腳"
                                   "步。\n" NOR);

        if (! (room = find_object(__DIR__"bridge1")))
                room = load_object(__DIR__"bridge1");

        if (! objectp(room))
                return notify_fail(HIW "你大叫道：BUG！BUG！\n" NOR);

        message_vision(HIW "\n只見$N" HIW "輕輕躍上獨木橋，飄然而"
                       "去。\n" NOR, me);
        me->move(room);
        message_vision(HIW "$N" HIW "從獨木橋上飄然而下，來到了山"
                       "峯的對面。\n" NOR, me);
        return 1;
}