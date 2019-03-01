inherit ROOM;

void create()
{
        set("short", "小路");
        set("long", @LONG
這裡是一條上山的小路。東北方有山賊出沒，要格外小心。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "northeast" : __DIR__"xiaolu4",
                "southdown" : __DIR__"xiaolu2",
        ]));
        set("objects",([
                __DIR__"npc/shanzei1" : 1,
        ]));

        set("coor/x", -49960);
        set("coor/y", 20020);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}