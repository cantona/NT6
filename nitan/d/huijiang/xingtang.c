// Room: /d/huijiang/xingtang.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "刑堂");
        set("long",@LONG
這裏是紅花會的刑堂。刑堂向來由追命十二郎執掌。會中弟子見到
他的那張冷冰冰的臉，往往都要打冷痙。大抵若有會眾違規逃亡，無論
天涯海角，石雙英的執法刀總能窮追而至，屢屢不爽。是故，會規才森
然一貫至今。
LONG );
        set("objects", ([
                CLASS_D("honghua")+"/shi-shuangying" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"wuchang",
        ]));
        set("coor/x", -50040);
        set("coor/y", 9130);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}