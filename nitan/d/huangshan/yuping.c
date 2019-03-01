// Room: /d/huangshan/yuping.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "玉屏樓");
        set("long", @LONG
這群高大的建築，因為背靠玉屏峰，所以又稱玉屏樓。在此可以盡
收玉屏，蓮花兩峰秀色。東觀天都，從山頂直落山腳，近乎垂直，西看
蓮花，恰似“突兀撐青穹”的盛開芙蓉。玉屏峰地處三大主峰中心，集
黃山奇景大成，“四海”煙雲氣吞山河，“三奇”美景疊現不窮。又稱
“黃山絕勝處”。
LONG
        );
        set("exits", ([ 
                "north"     : __DIR__"lianhua",
                "southeast" : __DIR__"yingke",
                "southwest" : __DIR__"lianrui",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huangshan");
        set("coor/x", -585);
        set("coor/y", -1040);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}