// guchang.c 曬穀場
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "曬穀場");
        set("long", @LONG
這裏是村莊中心的曬穀場，地方不大，不過村裏也就五、六户人
家，種的穀子也夠曬了。現在正是收穫的季節，穀場中堆滿了穀子，
幾個男女童子正在場中嬉鬧，不時地揚起一捧穀子相互撒去。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "southeast" : __DIR__"xiaocun",
                "north" : __DIR__"cunzhangjia",
                "northwest" : __DIR__"minju3",
                "southwest" : __DIR__"minju4",
        ]));
        set("objects", ([
                __DIR__"npc/boy" : 2,
                __DIR__"npc/girl" : 1,
        ]));

        set("coor/x", -12270);
	set("coor/y", 840);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}