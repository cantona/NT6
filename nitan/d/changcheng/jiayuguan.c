// Room: /d/changcheng/jiayuguan.c
// Last Modified by Winder on Aug. 25 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "嘉峪關箭樓");
        set("long", WHT @LONG
你站在號稱“天下第一雄關”的嘉峪關箭樓上，南面是終年積雪的
祁連山，北面是連綿起伏的馬鬃山，西望幾十裡地的一馬平川，真不愧
天下第一。長城在戈壁沙漠上的漫天黃沙中如蒼龍蠕動，若隱若現，忽
斷忽續。
LONG
NOR );
        set("outdoors", "xiyu");
        set("exits", ([
                "down"      : "/d/xingxiu/jiayuguan",
                "northeast" : __DIR__"changcheng21",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -18000);
        set("coor/y", 400);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}