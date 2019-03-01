// Room: /d/shaolin/twdian1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "東側殿");
        set("long", @LONG
這裡是東側殿。房間四周懸掛著達摩祖師、觀音大士的畫像，以
及一些寺內元老的字畫。地下散亂地放著許多蒲團，木魚等。看來此
處是本派弟子打坐修行之所。幾位中年和尚手持數珠，正在喃喃念經。
LONG );
        set("exits", ([
                "west" : __DIR__"twdian",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
