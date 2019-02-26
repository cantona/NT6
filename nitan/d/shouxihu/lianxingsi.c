// Room: /yangzhou/lianxingsi.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "蓮性寺");
        set("long", @LONG
蓮性寺舊名“法海寺”，始建於隋唐，重建於元代至元年間。康熙
帝南巡時賜名“蓮性寺”。山門面向東北，五楹，居中三間為天王殿，
內設佛龕，前坐彌勒，後立韋陀，兩廂列四天王。兩次間為樓房，後檐
上設方窗，下置板門。山門外兩翼築八字牆。
LONG );
        set("exits", ([
                "northeast" : __DIR__"pingtai4",
                "northwest" : __DIR__"shuixie",
                "southeast" : __DIR__"ouxiangqiao",
                "north"     : __DIR__"yunshange",
                "south"     : __DIR__"baitataji",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 60);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}