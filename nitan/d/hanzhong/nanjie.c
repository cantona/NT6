// nanjie.c 南街
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "南街");
        set("long", @LONG
這裡是漢中的南街，說是街，不過是一條小胡同而已。路上一個
人也沒有。街的盡頭有一扇小門。從這裡往北，就是漢中鎮的中心了。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "north" : __DIR__"zhongxin",
                "southeast" : __DIR__"fu-cemen",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12250);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}