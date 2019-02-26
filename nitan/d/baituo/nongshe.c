inherit ROOM;

void create()
{
        set("short", "農舍");
        set("long", @LONG
這裏是一間小農舍，傢俱很新。看來主人比較富裕。
LONG );
        set("exits", ([
                "west" : __DIR__"guangchang",
        ]));
        set("objects",([
                __DIR__"npc/woman" : 1,
        ]));
        set("coor/x", -49980);
        set("coor/y", 19980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}