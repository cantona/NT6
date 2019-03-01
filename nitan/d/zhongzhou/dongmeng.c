inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
這裡是中州的東城門。出城是一條大驛道，外地到中州的
人都從這裡進中州城，官府在這裡設關卡查問過往行人。一到
局勢不穩的時候這裡就特別的緊張。
LONG);
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/city/npc/wujiang" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"eroad1",
                  "west" : __DIR__"yanlingdong2",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -9000);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}