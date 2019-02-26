// Room: /d/hengshan/jinlongxia.c
// Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
        set("short", "金龍峽");
        set("long", @LONG
金龍峽又稱唐峪，是進入恆山的入口。恆山一名太恆山，或稱玄嶽，
是五嶽中的北嶽，道教以之為“第五小洞天”。它橫亙三百餘里，如一
隊行進中的隊列，昔人以為“恆山如行”來相對“泰山如坐”，“華山
如立”，“嵩山如卧”和“衡山如飛”。
LONG
        );
        set("exits", ([
                "southeast"  : __DIR__"cuipinggu1",
                "northeast"  : "/d/beijing/road6",
        ]));
        set("objects", ([
                CLASS_D("hengshan")+"/jing" : 1,
                "/d/motianya/npc/qiaofu" : 1,
        ]));
        set("outdoors", "hengshan");
//        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 3200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
