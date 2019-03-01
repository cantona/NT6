inherit ROOM;

void create()
{
        set("short", "匯珍園");
        set("long", @LONG
這是燕子塢中最大的花園，遍植江南的奇花異草，香氣濃鬱。彩
蝶在花間翩躚飛舞，你不由的痴了，有點樂而忘返。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "west"  : __DIR__"changlang",
        ]));
        set("objects", ([
            "/d/yanziwu/npc/hudie" : 3,
                "/clone/quarry/he" : 1,
        ]));
        setup();
        replace_program(ROOM);
}