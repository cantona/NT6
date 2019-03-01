inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
你走在一條石板路上，北面和南面都是習武堂，不少人在
這裡進進出出的，東面是郭府的客廳。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "east" : __DIR__"guofu_dating",
               "west" : __DIR__"guofu_shilu-4",
               "north" : __DIR__"guofu_xiwutang",
               "south" : __DIR__"guofu_xiwutang2",
        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}
