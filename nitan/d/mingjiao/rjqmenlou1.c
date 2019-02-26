//RJQMENLOU1.C

inherit ROOM;

void create()
{
        set("short", "門樓一層");
        set("long", @LONG
這裏是一間大石室，石室四周整齊的碼置着兵器架，十八般兵器
樣樣俱全。幾個教眾在室中巡邏，好像是守護兵器的。右面有一條石
梯直通樓上。
LONG );
        set("exits", ([
                "up" : __DIR__"rjqmenlou2",
                "east" : __DIR__"rjqyuan",
                "west" : __DIR__"tiekuang",
        ]));
        set("no_clean_up", 0);
//        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}