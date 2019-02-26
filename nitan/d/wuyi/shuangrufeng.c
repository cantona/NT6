// Room: /d/wuyi/shuangrufeng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "雙乳峯");
        set("long", @LONG
雙乳峯又名並蒂峯、鼓子峯，為八曲最高峯。遠遠望去，豐滿挺拔
而柔美，無不讓人驚歎和稱奇造化天工之所鍾。峯的兩面巖壁上，有一
巖洞，可容數十人，相傳為吳道人修煉所在，洞右小穴內還存放着有關
道人的遺蜕。這個洞就叫“吳公洞”。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northwest"  : __DIR__"path9",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -4960);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
