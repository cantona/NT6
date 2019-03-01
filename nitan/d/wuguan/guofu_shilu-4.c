inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
你走在一條石板路上，北面過去就是後院了，南面是西練
功場，西面傳來陣陣飯菜的香氣，那裡是郭府的飯廳。東面過
去是郭府大廳。
LONG);
        set("no_fight", 1);
        set("exits", ([
          	"east" : __DIR__"guofu_shilu-2",
          	"south" : __DIR__"guofu_lang3",
          	"north" : __DIR__"guofu_shilu-3",
          	"west" : __DIR__"guofu_fanting",
        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}
