inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
順山而走，山勢漸漸陡了起來，雜草荊棘叢生， 使你難以行走。
LONG );
        set("exits", ([
                "southwest" : __DIR__"road5",
                "eastup" : __DIR__"qingshan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -360);
        set("coor/y", -190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
