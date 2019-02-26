inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裏是郭府的後院，都是些幹活做事的地方，東面過去都
是柴房，西面是一個水房。人們忙碌的進出，幹着自己的活。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "east" : __DIR__"guofu_chaifang",
               "west" : __DIR__"guofu_shuifang",
               "north" : __DIR__"guofu_houyuan2",
               "south" : __DIR__"guofu_shilu-3",
        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}
