// Room: /yangzhou/baitaqingyun.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short","白塔晴雲");
        set("long",@LONG
白塔晴雲，位于蓮花橋北岸西側，與白塔隔湖相望。清乾隆按察使
銜程揚宗、揚州同知吳輔椿先後營構。白塔晴雲面湖而築，“別業臨青
甸，前軒枕大河”。園門面東，上嵌“白塔晴雲”石額。堂後庭院種植
瓊花、廣玉蘭、春梅、山茶、枇杷等四季花木，西院栽竹千竿，開門通
望春樓。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "northeast" : __DIR__"shuiyun",
                "southeast" : __DIR__"jicuixuan",
                "west"      : __DIR__"wangchunlou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}