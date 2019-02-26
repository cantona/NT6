// Room: /qingcheng/caochang.c
// Date: Aug. 10 1998 by Winder

inherit ROOM;
void create()
{
        set("short", "練功操場");
        set("long", @LONG
這裏是青城弟子練功習武之所，“冬練三九、夏練三伏”，出家人
往往勤快一些，往往天光才有魚肚白，這裏就有練功的影子。到得日出
山坳，便是滿場的人聲了。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "east"  : __DIR__"zoulang2",
                "west"  : __DIR__"zoulang3",
                "south" : __DIR__"zoulang1",
                "north" : __DIR__"songfengguan",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
                __DIR__"npc/fang" : 1,
                __DIR__"npc/dizi" : random(4),
        ]));
        set("coor/x", -8080);
        set("coor/y", -840);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}