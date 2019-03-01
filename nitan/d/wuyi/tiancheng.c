// Room: /d/wuyi/tiancheng.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "天成禪院");
        set("long", @LONG
虎嘯庵高居虎嘯巖上，明代即為武夷山釋道中心。清代康熙四十六
年，由于從浙江寧波天童寺來了一位名聲顯赫的泉聲和尚，並進庵任主
持，虎嘯庵才正式易名為「天成禪院」。據虎嘯巖望去，其秀無比，其
峻無雙，它的險要曾令不少遊人生畏，望而卻步。明代釋真熾在詩中寫
道：「極目皆圖畫，居然與世違。」
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "northdown" : __DIR__"huxiaoyan",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng": random(3),
        ]));
        set("coor/x", 1390);
        set("coor/y", -5040);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
