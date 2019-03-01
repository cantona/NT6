//room: xiaojing.c
inherit ROOM;

void create()
{
        set("short","小徑");
        set("long", @LONG
這是個一條湖邊的小徑，西面就是一座小橋。周圍湖光影天，你
不禁深吸了一口醉人的空氣，陶醉於山水中。
LONG );
        set("outdoors", "yanziwu");
        set("exits",([
            "west"  : __DIR__"xiaoqiao",
            "south" : __DIR__"xiaoting",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
