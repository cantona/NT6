#include <ansi.h>; 
inherit ROOM;

void create()
{
        set("short", "獨木橋");
        set("long", @LONG
四下無聲，仰視蒼天，注視雪白的山峯，令人不覺愴然而
發思古之幽情。往前只見一道飛巖，下臨絕崖，只有一條狹窄
的獨木橋(bridge)通達對崖，危橋在穀風中不停地抖動。
LONG);
        set("outdoors", "gaochang");

        set("exits", ([ 
                "south" : __DIR__"xiaojing",
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

        if (! (room = find_object(__DIR__"bridge2")))
                room = load_object(__DIR__"bridge2");

        if (! objectp(room))
                return notify_fail(HIW "你大叫道：BUG！BUG！\n" NOR);

        message_vision(HIW "\n只見$N" HIW "輕輕躍上獨木橋，飄然而"
                       "去。\n" NOR, me);
        me->move(room);
        message_vision(HIW "$N" HIW "從獨木橋上飄然而下，來到了山"
                       "峯的對面。\n" NOR, me);
        return 1;
}