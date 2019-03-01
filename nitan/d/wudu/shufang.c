inherit ROOM;

void create()
{
        set("short", "書房");
        set("long", @LONG
這裡便是教主平時日內看書的地方，房間不大，只靠窗擺著一張
書案，案邊放了幾本書，看來是教主經常翻看的。
LONG);

        set("exits", ([
                "south" : __DIR__"dating",
        ]));

        set("objects", ([
                 __DIR__"obj/book2": 1,
        ]));

        setup();
        replace_program(ROOM);
}
