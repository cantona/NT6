// maco 2/17/2000

inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
這是條偏僻的小徑，蜿蜒地繞入白駝山，四周悄然無聲。遙望北
方，是一座深邃的山谷，氣氛陰森，那就是白駝山的蛇谷。東邊的岔
路通往白駝山莊的蛇場。
LONG );
        set("exits", ([ 
                "east"  : __DIR__"shechang",
                "north" : __DIR__"shegu1",
                "south" : __DIR__"barn",
        ]));
        set("objects",([
                "/clone/beast/jinshe" : random(3),
                "/clone/beast/dushe"  : 1 + random(3),
                "/clone/beast/fushe"  : random(2),
                "/clone/beast/qingshe": random(2),
                "/clone/beast/wubushe": random(3),
        ]));

        set("outdoors","baituo");
        replace_program(ROOM);
        set("coor/x", -49970);
        set("coor/y", 20100);
        set("coor/z", 30);
        setup();
}