// shijie3.c 石階
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這是一條整齊的石板路，依山而建，隨着山勢的曲折蜿蜒曲折。
由於山勢陡了，當初修建這條石階時肯定費了不小的功夫。走到這
裏，已經可以看見全真教重陽觀的檐角了。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "northwest" : __DIR__"shijie2",
                "eastup" : __DIR__"shijie4",
        ]));
        set("objects",([
        //      __DIR__"npc/youke" : 1,
                __DIR__"npc/xiangke" : 1,
        ]));

        set("coor/x", -3160);
        set("coor/y", 120);
        set("coor/z", 140);
        setup();
        replace_program(ROOM);
}