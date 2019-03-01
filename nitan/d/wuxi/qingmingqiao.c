// Room: /d/wuxi/qingmingqiao.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "清名橋");
        set("long", @LONG
清名橋是南門外有名的一座古橋，它原名清寧橋，也稱清明橋。江
南運河在城中曲曲折折地流淌，又匯到這裡的護城河中。橋身用紫褐色
和青黃色的花崗石砌成，站在橋中可眺望南門外的林蔭道。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"southgate",
                "south" : __DIR__"road7",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1040);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}