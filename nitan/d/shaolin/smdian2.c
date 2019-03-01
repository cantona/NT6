// Room: /d/shaolin/smdian2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "西側殿");
        set("long", @LONG
這裡是西側殿。房間四周懸掛著達摩祖師、觀音大士的畫像，以
及一些寺內元老的字畫。地下散亂地放著許多蒲團，木魚等。看來此
處是本派弟子打坐修行之所。幾位年輕僧人正肅容入定，看來已頗得
禪宗三昧。
LONG );
        set("exits", ([
                "east" : __DIR__"smdian",
        ]));
        set("objects",([
                __DIR__"obj/muchui" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
