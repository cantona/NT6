inherit ROOM;

void create()
{
        set("short", "小道");
        set("long", @LONG
你走到這裡，一條小道蜿延曲折地通向遠方，兩旁是鬱鬱蔥蔥的
樹林，微風吹過，樹葉發出奚索的聲音。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "north" : __DIR__"xiaodao2",
                "south" : __DIR__"huayuan",
        ]));
        set("objects",([
                "/d/baituo/npc/cungu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}