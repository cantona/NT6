// Room: /d/yanping/9fengshan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "九峯山");
        set("long", @LONG
九峯山隔西溪與府城相望。因九峯重疊居周遭諸峯之冠，故名。山
上環境幽靜，樹木蒼鬱。“九峯月朗”為延平八景之一。宋代的大儒李
侗、朱熹曾在這裏講學，讚美九峯景緻為“九朵芙蓉”、“九疊翠屏”。
LONG );
        set("exits", ([
                "east"      : __DIR__"shuyuan",
                "southup"   : __DIR__"baoyunsi",
                "northdown" : __DIR__"fuqiao2",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : 2,
        ]));
        set("outdoors", "yanping");
        set("coor/x", 1480);
        set("coor/y", -6220);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}