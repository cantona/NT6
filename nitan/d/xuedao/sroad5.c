inherit ROOM;

void create()
{
        set("short", "大雪山口");
        set("long", @LONG
這兒遍地冰雪，你眼前白皚皚的一片。
LONG );
        set("exits", ([
                "eastdown"  : __DIR__"sroad4",
                "southup"   : __DIR__"sroad6",
        ]));
        set("outdoors", "xuedao");
        setup();
        replace_program(ROOM);
}