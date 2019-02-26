inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
  這裏是雪山寺內的走廊。這裏有點幽暗，天花板上有一些不知道
確切含義的雕刻，牆壁上則是很通俗的佛經故事壁畫了。壁上點着幾
碗大海燈照明。
LONG );
        set("exits", ([
                "southdown" : __DIR__"cedian2",
                "east"      : __DIR__"dating",
                "north"     : __DIR__"zoulang4",
        ]));
        setup();
}