//ROOM: /d/yanziwu/changlang.c

inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
只見紅欄碧瓦，一派富貴氣象，不時有幾隻燕子靈巧的從廊見飛
過，長廊的盡頭有一座大花園。長廊上似乎還有一層，你忍不住想爬
上去看看。
LONG );
        set("exits", ([
            "east"  : __DIR__"huizhen",
            "west"  : __DIR__"lixiang",
            "north" : __DIR__"shijian",
            "south" : __DIR__"huayuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}