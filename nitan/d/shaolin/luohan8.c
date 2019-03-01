// Room: /d/shaolin/luohan8.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "羅漢堂八部");
        set("long", @LONG
這是一間極為簡陋的禪房。環視四周，除了幾幅佛竭外，室內空
蕩蕩地別無他物。地上整齊的擺放着幾個破爛且發黑的黃布蒲團，幾
位鬚髮花白的老僧正在坐在上面閉目入定。這裏是本寺十八羅漢參禪
修行的地方，不少絕世武功便是在此悟出。
LONG );
        set("exits", ([
                "south" : __DIR__"luohan7",
                "north" : __DIR__"luohan9",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/cheng-mie" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
