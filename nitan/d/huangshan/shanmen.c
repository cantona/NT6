// Room: /d/huangshan/shanmen.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "黃山山門");
        set("long", @LONG
這是一座石雕門坊，過了山門後，便是黃山，這裏地屬丘陵，古代
稱為黔山，因山色黝黑，遠望如黛得名，後因唐明皇聽信“黃帝在此飛
升”，所以改為黃山。連綿百里，羣峯無數，引來無數遊人。過山門後，
便是温泉。
LONG
        );
        set("exits", ([ 
                "northup"   : __DIR__"wenquan", 
                "southwest" : "/d/henshan/hsroad2",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -595);
        set("coor/y", -1110);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}