inherit ROOM;

void create()
{
        set("short", "尚書府");
        set("long", @LONG
這裏是京城尚書府了，兵部尚書趙大人經常在這裏會客，和接見
往來傳遞軍情的前線使者。
LONG );
        set("outdoors", "city2");
        set("no_fly",1);

        set("exits", ([
                "west" : __DIR__"ssfmen",
        ]));

        set("objects", ([
               __DIR__"npc/zhao":  1,
        ]));

        setup();
        replace_program(ROOM);
 }