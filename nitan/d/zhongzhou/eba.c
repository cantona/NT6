inherit ROOM;

void create()
{
        set("short", "漕幫");
        set("long", @LONG
這裡是漕幫的總部，說是什麼漕幫，其實就是幾個惡霸勾
結在一起在菜場這一塊地方收收保護費，幫人打打架。幾個流
氓正往裡屋去。
LONG);

        set("exits", ([
                "north" : __DIR__"canchang",
                "enter" : __DIR__"liwu",                 
        ]));

        set("outdoors", "zhongzhou");
        set("coor/x", -9009);
	set("coor/y", -989);
	set("coor/z", 1);
	setup();
        replace_program(ROOM);
}