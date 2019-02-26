inherit ROOM;

void create()
{
        set("short", "洞口");
        set("long", @LONG
這裏是山賊的老窩的洞口，幾個山賊把守在洞前，來回的巡視着，
守備很是森嚴。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "north" : __DIR__"dongnei",
                "south" : __DIR__"xiaolu4",
        ]));

        set("objects",([
                __DIR__"npc/shanzei2" : 2,
        ]));

        set("coor/x", -49950);
        set("coor/y", 20040);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}