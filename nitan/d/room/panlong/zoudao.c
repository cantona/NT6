// yingke.c 盤龍居迎客廳

#include <room.h>

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "走道");
        set("long", @LONG
這是連接正廳和大門的一條走道，兩旁都是木制牆板，前面就是
迎客廳。
LONG );

        set("default_long", "這是連接正廳和大門的一條走道，兩旁都是木" /* EXAMPLE */
                            "制牆板，前面就是迎客廳。" );              /* EXAMPLE */
                                                                       /* EXAMPLE */

        set("exits", ([
                "north"  : __DIR__"yingke",
                "south"  : __DIR__"qianting",
        ]));

        set("gate", "close");

//**    set("objects", ([
//**            "/d/room/roomnpc/yahuan" : 1,
//**    ]));

        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}

void init()
{
        add_action("do_push", "push");
        add_action("do_close", "close");
}

int do_push(string arg)
{
        object me;
        object room;

        if (query("gate") == "open")
                return notify_fail("大門開著呢，你還推什麼？\n");

        me = this_player();
        message("vision",  "你用力推了推大門，就聽大門“吱呀呀”的被人推開了。\n",
                           this_object());
    
        room = get_object(__DIR__"qianting");
        message("vision", "大門“吱呀呀”的被人推開了。\n", room);
        set("gate", "open");
        set("exits/south", __DIR__"qianting");
        set("exits/north", __FILE__, room);
        set("gate", "open", room);
        remove_call_out("do_close");
        call_out("do_close", 10, 0, 1);
        return 1;
}

int do_close(string arg, int n)
{
        object me;
        object room;

        if (query("gate") == "close")
                return notify_fail("大門關著呢，你還再關一遍？\n");

        if (! n)
        {
                me = this_player();
                message("vision", me->name() + "走上前去，用力合上大門。\n",
                        this_object());
        } else
        {
                message("vision", "大門“吱呀呀”的被人關上了。\n",
                        this_object());
        }

        room = get_object(__DIR__"qianting");
        message("vision", "大門“吱呀呀”的被人關上了。\n", room);
        set("gate", "close");
        delete("exits/south");
        set("gate", "close", room);
        delete("exits/north", room);
        return 1;
}
