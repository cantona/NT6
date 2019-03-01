// shijianyan.c 試劍巖
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "試劍巖");
        set("long", @LONG
石階旁立著一塊大巖石，上面斑斑駁駁的盡是砍傷。這塊大巖
石便是全真教的試劍巖，天下的英雄來到這裡，望著先輩們練劍時
在巖石上的砍痕，無不肅然起敬。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northdown" : __DIR__"shijie4",
                "southup" : __DIR__"shijie8",
                "east" : __DIR__"jiaobei",
        ]));
        set("objects",([
                CLASS_D("quanzhen")+"/yin" : 1,
                __DIR__"npc/daotong" : 2,
        ]));

        set("coor/x", -3150);
        set("coor/y", 110);
        set("coor/z", 160);
        setup();
        replace_program(ROOM);
}