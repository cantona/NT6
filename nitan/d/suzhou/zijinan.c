// Room: /d/suzhou/zijinan.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "紫金庵");
        set("long", @LONG
這是一座蘇州城裏有名的寺庵，庵中正面是釋加摩尼佛眼，似乎在
注視前來禮佛之人；右壁一尊諸天用三個手指托起一塊輕柔的繡花經蓋
和後壁觀音菩薩頭上的一頂刻着牡丹花的紫紅色華蓋。左壁的每尊羅漢
塑像造型生動，各具特徵，到達了以神人話、精神超忽、呼之慾活的藝
術境界，令人歎為觀止。
LONG );
        set("objects", ([
                __DIR__"obj/box" : 1,
                __DIR__"npc/nigu1" : 1,
                __DIR__"npc/nigu2" : 1,
        ]));
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("no_fight", "1");
        set("exits", ([
                "east"      : __DIR__"beidajie2",
        ]));
	set("coor/x", 1100);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}