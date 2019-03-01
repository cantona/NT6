// shijie9.c 石階
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這是一條整齊的石板路，依山而建，隨著山勢的曲折蜿蜒曲折。
由于山勢陡了，當初修建這條石階時肯定費了不小的功夫。走到這
裡，已經可以看見全真教重陽觀的檐角了。西面好象有一條小路。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "south"     : __DIR__"guanritai",
                "northdown" : __DIR__"shijie8",
        ]));
        set("objects",([
                __DIR__"npc/daotong" : 2,
                "/clone/npc/walker"  : 1,
        ]));

        set("coor/x", -3150);
        set("coor/y", 90);
        set("coor/z", 180);
        setup();
        replace_program(ROOM);
}
