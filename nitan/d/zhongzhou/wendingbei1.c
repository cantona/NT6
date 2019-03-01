inherit ROOM;

void create()
{
        set("short", "文定北街");
        set("long", @LONG
這是中州文定北街，寬敞的街道看的人不竟心情一暢。街
道的東面有一座酒樓，因離街不遠，裡面劃拳喝酒聲音歷歷在
耳。聽的在耳你也不覺想去痛飲一杯。西面有條小巷。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"yinghao",
                "south" : __DIR__"shizhongxin",
                "west" : __DIR__"xiaoxiang",
                "north" : __DIR__"wendingbei2",
        ]));

        set("objects", ([
                __DIR__"npc/xianren" : 1,
                __DIR__"npc/kid1": 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}