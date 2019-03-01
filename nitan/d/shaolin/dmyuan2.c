// Room: /d/shaolin/dmyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "達摩院二樓");
        set("long", @LONG
這是一座古樸的殿堂。西首的牆上掛滿了各類武功圖譜，不少白
須白眉的老僧們正端坐在圖譜畫軸之前，似乎在苦苦思索。南北山牆
是高及屋頂的大書架，走近細看，它們是各門各派的武功秘笈，屋正
中擺著幾張矮幾訶和幾個團，幾位老僧正在入定中。
LONG );
        set("exits", ([
                "down" : __DIR__"dmyuan",
        ]));
        set("objects",([
                CLASS_D("shaolin") + "/xuan-bei" : 1,
                "/clone/book/xisuijing" : 1,
                __DIR__"npc/xiao-bei" : 1,
        ]));
        set("no_magic", 1);
        setup();
}

int valid_leave(object me, string dir)
{
        if (present("xisui jing", me))
                return notify_fail("本寺最高心法不見了，你怎敢就走？\n");
        return 1;
}
