inherit ROOM;

void create()
{
        set("short", "武器店");
        set("long", @LONG
這家武器店和街對面的盔甲店都是同一個老闆開的，之所以把它們分
開，只是為了方便顧客購買自己需要的東西，店內四壁上掛滿了各式個樣
的兵器，金制的，銀製的，銅製的，鐵製的，皮製的，品種齊全，應有盡
有。
LONG);
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"eroad1",
        ]));
        set("objects", ([
                __DIR__"npc/zhu2" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}