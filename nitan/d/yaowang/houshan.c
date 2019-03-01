inherit ROOM;

void create()
{
        set("short", "後山");
        set("long", @LONG
這是一間巨大的瓦房，房子裡被直到屋頂的大木架子佔滿了，
樹堆上坐著一位老人。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"ycl9",
]));

        set("objects", ([
        "/kungfu/class/yaowang/shiwanchen" : 1,
]));
        setup();
        replace_program(ROOM);
}
