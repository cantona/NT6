// Room: /d/yueyang/ximen.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "岳陽西門");
        set("long", @LONG
這裏是岳陽城樓的西門，門內也沒有官兵看守，大概這裏是丐幫的
天下，岳陽府城的治安也就實質上給丐幫接管了。官府也不大關心如何
如何的，反正只要丐幫合作，倒也路不拾遺、夜不閉户的。
LONG );
        set("outdoors", "yueyang");
        set("no_clean_up", 0);
        set("exits", ([
                "east"     : __DIR__"xijie",
                "northup"  : __DIR__"loumen",
                "westdown" : __DIR__"shijie7",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/xiang" : 1,
        ]));
	set("coor/x", -6220);
	set("coor/y", -3010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}