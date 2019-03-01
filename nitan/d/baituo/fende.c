inherit ROOM;

void create()
{
        set("short", "墳地");
        set("long", @LONG
這裡是一片荒涼陰森的荒墳地，時不時傳來幾聲烏鴉的叫聲。有
位中年婦女正在這裡吊喪，哭泣個不停。
LONG );
        set("outdoors", "baituo");

        set("exits", ([
                "southwest" : __DIR__"xiaolu1",
        ]));

        set("objects" , ([
                __DIR__"npc/guafu" : 1,
        ]));

        set("coor/x", -49960);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}