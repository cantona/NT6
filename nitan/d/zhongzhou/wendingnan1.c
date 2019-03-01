inherit ROOM;

void create()
{
        set("short", "文定南街");
        set("long", @LONG
這是中州文定南街，寬敞的街道看的人不竟心情一暢。街
道的東面熙熙攘攘的是一個菜場。西面的一家店面，一聽裡面
的算盤聲就知道是一家不小的錢莊。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"canchang",
                "south" : __DIR__"wendingnan2",
                "west" : __DIR__"bank",
                "north" : __DIR__"shizhongxin",
        ]));
        set("objects", ([
                "/d/city/npc/liumang" : 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}