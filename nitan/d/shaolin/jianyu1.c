// Room: /d/shaolin/jianyu1.c
// Date: YZC 96/02/06

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "監獄");
        set("long", @LONG
這裡黑沉沉的，即無一絲光亮，也無半分聲息。黑暗中依稀可以
看到身邊似乎有幾個人影，看到你轉過頭去，他們立刻屏住呼吸，緊
張地瞪著你。四壁摸上去冰涼，且極硬，似乎都是鋼鐵鑄成，只有南
北面各有一道小門，門上開了個巴掌大的洞，象是送飯用的。腳邊有
一堆東西踢上去克剌剌地散了開來，細看卻是一具白得發亮的枯骨。
LONG );
        set("exits", ([
                "north" : __DIR__"jianyu",
        ]));
        set("objects",([
                "/d/shaolin/npc/yu-zu" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
