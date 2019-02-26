// Room: /d/yanziwu/garden.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裏是蔓陀山莊的花園，鳴鶯啼柳，草碧花濃，果然是江南好春色。
尤其引人注目的是園中的幾盆茶花，在大理雖非上品，在江南卻委實難
得。一道溪水潺潺，自園中穿過，順帶聚出一彎小湖。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "north"  : __DIR__"yunjin1",
                "south"  : __DIR__"path4",
                "east"   : __DIR__"path5",
                "west"   : __DIR__"path25",
        ]));
        set("objects", ([
                "/d/dali/obj/chahua1": 1,
        ]));
        set("coor/x", 1230);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}