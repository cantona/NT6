// Room: /d/wuyi/tianyoupath.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天遊石徑");
        set("long", @LONG
你正攀爬在天遊石徑上。整個天遊峯就是一塊渾然的大石頭。所以
有“一塊石頭玩半天”的説法。天遊石徑就鑿在陡峭的石面上，上看青
天，下臨無地，眼前就是光溜溜的石面。抬頭就是前一個人的腳跟，萬
丈深淵下是如蟻蠕動的人羣排成一線。
人。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "westup"   : __DIR__"tianyoufeng",
                "eastdown" : __DIR__"chadong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1400);
        set("coor/y", -4970);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
