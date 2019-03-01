// Room: /binghuo/wangpangu1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "谷口");
        set("long", @LONG
走近山谷，前面向南就是群雄聚會之處。王盤山島正當海潮生息
之所，海風勁烈，風勢在這谷口裡聚焦，更是吹得滿山樹枝亂舞，沙
塵漫天。往南望去，只見山谷裡一片青草地上擺著七八張方桌，除了
東首第一席外，每張桌旁都已坐了人。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("exits", ([
                "north" : __DIR__"wangpanshan",
                "south" : __DIR__"wangpangu2",
        ]));
        setup();
        replace_program(ROOM);
}
