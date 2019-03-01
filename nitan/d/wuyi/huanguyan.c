// Room: /d/wuyi/huanguyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "換骨巖");
        set("long", @LONG
換骨巖在幔亭峰之北，相傳是武夷十三仙在次換骨成仙。于是，這
裡就成了人間和仙界的分水嶺。巖上靈雲洞中七股泉水交相流淌，稱為
七星泉。雲虛洞內寬達數丈，內有小樓，不施片瓦，風雨不侵，俗稱“
仙女梳妝樓”。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"sangufeng",
                "south"     : __DIR__"mantingfeng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -4960);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
