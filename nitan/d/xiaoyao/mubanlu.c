// mubanlu.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "木板路");
        set("long", @LONG
這是一條用木板鋪成的小道，雖然不是很長，但是卻看得出鋪得十
分細心，連一些細微的疏忽也注意到了。道路兩旁種着一些奇花異樹，
使過路人有心曠神怡的感覺。
LONG );
        set("exits", ([
                "south" : __DIR__"muwu3",
                "north" : __DIR__"xiaodao4",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xiaoyao");
        set("coor/x", 90);
        set("coor/y", -510);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}