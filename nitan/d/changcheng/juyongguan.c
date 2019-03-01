// Room: /d/changcheng/juyongguan.c
// Last Modified by Winder on Aug. 25 2000
#include <ansi.h>

inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", "居庸關");
        set("long", WHT@LONG
這裡就是長城上著名的雄關──居庸關。這裡風景優美，滿山遍野
的楓樹，一到秋天所有的楓葉都變成了紅色，把這裡變成了一片紅色的
海洋。當年，康熙皇帝到這裡遊玩時，被這美麗的景色吸引，親筆提下
了“居庸疊翠”四個大字。
    由于從這裡向北通向關外廣闊無垠的蒙古大草原，向西可以前往西
域，許多從京城逃出來的罪犯都是從這裡逃出去，所以城牆上貼滿了官
府的告示(gaoshi)，而守衛的官兵也戒備森嚴，隨時盤問著可疑的人。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west"  : __DIR__"changcheng1",
                "east"  : __DIR__"badaling",
                "north" : "/d/mobei/huanglu1",
                "south" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));
        set("coor/x", -190);
        set("coor/y", 5000);
        set("coor/z", 0);
        setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n         居庸總兵\n      風城主\n";
}