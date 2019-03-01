inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
順山而走，山勢漸漸陡了起來，雜草荊棘叢生， 使你難以行走。
LONG );
        set("exits", ([
                "westup" : __DIR__"qingshan",
                "eastdown" : __DIR__"road4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -340);
        set("coor/y", -190);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
