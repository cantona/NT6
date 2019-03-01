// Room: /d/wuyi/huxiaoyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "虎嘯巖");
        set("long", @LONG
這裡是武夷山屈指可數的獨具泉天趣的佳境之一。所謂「虎嘯」出
于古時有仙，曾騎虎嘯于巖上的典故。虎嘯巖上有個巨洞每當山風掠過
該洞，該洞就會發出近似虎嘯之聲。聲小之時，只能穿耳閃過，宏亮之
時，卻可聲震群山，令人毛骨悚然。抵達虎嘯巖下，抬頭望巖，首先映
入眼簾是「虎溪靈洞」四個大字高勒巖壁，向來往的遊人提示：危崖高
聳，岌岌可危，幽深景觀，虎嘯神奇。李綱遊覽虎嘯巖，題詩：「昔年
雕虎嘯幽巖，千裡清風皺碧潭。」
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"   : __DIR__"jingtai",
                "south"   : __DIR__"path6",
                "southup" : __DIR__"tiancheng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -5030);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
