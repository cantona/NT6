inherit ROOM;

void create()
{
        set("short", "西郊");
        set("long", @LONG
這是中原第一府「中州府」的郊外。這兒離中州不遠，治
安也還說得過去。西面是洛陽城方向，東邊通向中州府。
LONG);
        set("exits", ([
                //"west" : __DIR__"wroad1",
               "west" : "/d/luoyang/hulaoguan",
                  "east" : __DIR__"chenglou",
        ]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -9090);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}