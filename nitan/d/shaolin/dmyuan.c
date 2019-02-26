// Room: /d/shaolin/dmyuan.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "達摩院");
        set("long", @LONG
這是一座古樸的殿堂。西首的牆上掛滿了各類武功圖譜，不少白
須白眉的老僧們正端坐在圖譜畫軸之前，似乎在苦苦思索。南北山牆
是高及屋頂的大書架，走近細看，它們是各門各派的武功祕笈，屋正
中擺着幾張矮几訶和幾個團，幾位老僧正在入定中。西首有個樓梯上
樓。
LONG );
        set("exits", ([
                "southdown" : __DIR__"wuchang3",
                "northdown" : __DIR__"guangchang5",
                "up"        : __DIR__"dmyuan2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
