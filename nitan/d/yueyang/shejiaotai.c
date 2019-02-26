// Room: /d/yueyang/shejiaotai.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "射蛟台");
        set("long", @LONG
射蛟台又名射蛟浦，在酒香亭東面。這是一懸空而立橫卧洞庭湖中
的巨石。相傳漢代有一巨蛟，在水中興風作浪，勞命傷財，漢武帝聞之
便率兵巡狩，在君山射蛟於浦口。巨石頂上有個三米見方平面，上有兩
個二尺多長的巨大腳印，傳為漢武帝射蛟時留下的聖蹟，此台集幽峭、
險峻於一體，為君山八景之一。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"xiaolu2",
                "westup" : __DIR__"shijie3",
        ]));
        set("objects", ([
                CLASS_D("gaibang")+"/song" : 1,
        ]));
        set("coor/x", -1740);
        set("coor/y", 2280);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}