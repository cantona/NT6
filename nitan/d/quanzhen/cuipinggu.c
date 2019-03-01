// cuipinggu.c 翠屏谷
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "翠屏谷");
        set("long", @LONG
你的面前是一座形如屏風的大山壁，山壁上鬱鬱蔥蔥都是樹，一
眼看過去，全是一片翠綠色。這就是此地名叫翠屏谷的由來。從這裡
繼續北上，就到了終南山上的柏樹林了。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southdown" : __DIR__"shanlu2",
                "northup" : __DIR__"baishulin1",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", 20);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
