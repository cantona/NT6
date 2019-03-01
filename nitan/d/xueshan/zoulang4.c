inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
 這裡是雪山寺內的走廊。這裡有點幽暗，天花板上有一些不知道
確切含義的雕刻，牆壁上則是很通俗的佛經故事壁畫了。壁上點著幾
碗大海燈照明。
LONG );
        set("exits", ([
                "east"  : __DIR__"neidian",
                "south" : __DIR__"zoulang2",
        ]));
        setup();
        replace_program(ROOM);
}