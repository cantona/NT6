inherit ROOM;

void create()
{
        set("short", "蛇園");
        set("long", @LONG
這裏是白駝山莊的蛇園。白駝山以毒名揚天下，最重要的毒質就
來自毒蛇。這裏遍地是蛇，牆上也巴着蛇，屋檐上也向下垂着蛇，樹
枝上也盤繞着蛇，不由你不心驚。
LONG );
        set("exits",([
                "north"      : __DIR__"road1",
                "west"       : __DIR__"tuyuan",
        ]));
        set("outdoors", "baituo");
        set("objects", ([
                "/clone/beast/jinshe" : random(3),
                "/clone/beast/dushe"  : 1 + random(3),
                "/clone/beast/fushe"  : random(2),
                "/clone/beast/qingshe": random(2),
                "/clone/beast/wubushe": random(3),
        ]));
        set("coor/x", -49970);
        set("coor/y", 20070);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}