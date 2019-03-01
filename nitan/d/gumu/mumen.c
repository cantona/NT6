#include <ansi.h>
inherit ROOM;

int do_move(string arg);

void create()
{
        set("short", "墓門");
        set("long", @LONG
你走過了草地，眼前突然了一片開闊地，突兀地聳立著一座大墓，
墓上砌的石頭已經班駁了，看的出來這是座古墓。墓前沒有立碑，也
沒有任何的標記，不知道這是前朝哪位王公大臣的墓穴。墓門口被一
塊的大石頭(shi)封閉得絲毫不透。
LONG );
        set("outdoors", "gumu");
        set("exits", ([
                "east"  : __DIR__"xuanya",
                "west"  : __DIR__"huangshalin",
                "north" : __DIR__"caodi",
        ]));

        set("objects", ([
               __DIR__"npc/yufeng" : 1+random(3),
               __DIR__"npc/sun" :  1,
        ]));

        set("item_desc", ([
               "shi": HIC "這是塊巨石，怕不有萬斤上下，好象錈著「" NOR + YEL"降龍石" HIC
                      "」幾個字。\n" NOR,
        ]) );
        set("coor/x", -3220);
        set("coor/y", 30);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_move", "luo");
        add_action("do_move", "tui");
}

int do_move(string arg)
{
        object me=this_player();

        if( !arg || arg != "shi" ) {
                return notify_fail("你要移動什麼？\n");
        }

        if( (int)me->query_str() > 33 ) {
                message_vision(HIC "$N" HIC "站在石前，雙掌發力推動巨石，只聽得巨石"
                       "吱吱連聲，緩\n緩向後移去，現出一道門戶來。\n" NOR,
                       this_player());
                set("exits/south", __DIR__"mudao01");
                remove_call_out("close");
                call_out("close", 5, this_object());
        } else
                message_vision("$N試著推了推巨石，巨石紋絲不動，只得罷了。\n", this_player());
        return 1;
}

void close(object room)
{
        message("vision", HIW "\n只見巨石又吱吱地回到原地。\n" NOR, room);
        delete("exits/south", room);
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "south"
           || ! objectp(guard = present("sun popo", this_object()))
            || !query("family", me) )
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}