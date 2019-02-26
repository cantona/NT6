inherit ROOM;

void create()
{
        set("short", "小道");
        set("long", @LONG
你走到這裏，一條小道蜿延曲折地通向遠方，兩旁是鬱鬱葱葱的
樹林，微風吹過，樹葉發出奚索的聲音。
LONG );
        set("outdoors", "lingjiu");

        set("exits", ([
            "north" : __DIR__"men3",
            "south" : __DIR__"xiaodao1",
        ]));
        set("objects",([
                "/d/beijing/npc/kid1" : 1,
        ]));
        setup();
        replace_program(ROOM);
}