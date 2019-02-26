// Room: /d/huanggong/mishi.c
#include <room.h>
inherit ROOM;

void close_gate();
int do_open(string arg);
int do_close(string arg);

void create()
{
        set("short", "暗室");
        set("long", @LONG
這是康熙與心腹大臣密謀大事的地方, 尋常人是進不來的.
LONG
        );

        set("objects", ([
                "/d/beijing/obj/book14_8" : 1,
                __DIR__"obj/feicui" : 1,
        ]));

        set("coor/x", -190);
        set("coor/y", 5281);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_open", "open");
        add_action("do_open", "unlock");
}

void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"yushufang")) )
                room = load_object(__DIR__"yushufang");
        if(objectp(room))
        {
                delete("exits/south");
                message("vision","只聽乒地一聲，暗門自動關了起來。\n", this_object());
                message("vision","你腦海中閃過一個念頭：壞了！出不去了！\n", this_object());
                delete("exits/north", room);
                message("vision","只聽乒地一聲，暗門自動關了起來。\n",room);
                message("vision","你腦海中閃過一個念頭：哎喲！又進不去了！\n", room );
        }
}

int do_open(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("暗門已經是開着了。\n");

        if (!arg || (arg != "door" && arg != "south"))
                return notify_fail("你要開什麼？\n");

        if(!( room = find_object(__DIR__"yushufang")) )
                room = load_object(__DIR__"yushufang");

        if(objectp(room))
        {
                set("exits/south", __DIR__"yushufang");
                message_vision("$N使勁把暗門打了開來。\n",this_player());
                set("exits/north", __FILE__, room);
                message("vision","裏面有人把暗門打開了。\n",room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }
        return 1;
}