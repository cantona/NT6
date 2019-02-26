inherit ROOM;

void create()
{
        set("short", "雲海石");
        set("long", @LONG
這裏放着一座碩大的石頭。乃是白自在從雪山絕谷中找到的
奇石。只見上面雲氣繚繞，佈滿了一些奇形怪狀的花紋。聽説在
要下雨的時候，還會散發出不同形狀的雲霧，繚繞奇石四周，經
久不散，是白自在最喜歡來賞玩的寶物。
LONG );
        set("outdoors", "lingxiao");
        set("exits", ([
                    "east" : __DIR__"meiroad2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}