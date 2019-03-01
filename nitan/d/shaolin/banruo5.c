// Room: /d/shaolin/banruo5.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "般若堂五部");
        set("long", @LONG
這是一間極為簡陋的禪房。環視四周，除了幾幅佛竭外，室內空
盪盪地別無他物。地上整齊的擺放著幾個破爛且發黑的黃布蒲團，幾
位須發花白的老僧正在坐在上面閉目入定。這裡是本寺十八羅漢參禪
修行的地方，不少絕世武功便是在此悟出。一位小沙彌在一邊垂手站
立。
LONG );
        set("exits", ([
                "east" : __DIR__"wuchang1",
                "south" : __DIR__"banruo4",
                "north" : __DIR__"banruo6",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/xuan-nan" : 1,
                CLASS_D("shaolin") + "/cheng-zhi2" : 1,
                __DIR__"npc/xiao-nan" : 1
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
