// Room: /d/shaolin/jianyu.c
// Date: YZC 96/02/06

#include <ansi.h>

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
                "south" : __DIR__"jianyu1",
        ]));
        set("valid_startroom",1);
        set("objects",([
                CLASS_D("shaolin") + "/qing-yuan" : 1,
                "d/shaolin/obj/fojing1"+random(2) : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
}

void init()
{       
        object ob = this_player();

        if( (int)ob->query_condition("bonze_jail") <= 0 )
        {
                message("vision",
                        HIY "只聽牢房鐵門匡地一響，一個昏昏沉沉的家伙被扔了進來！\n\n" NOR, 
                        environment(ob), ob);

                tell_object(ob, "獄卒嘿嘿地笑著：今兒個你可落在我手裡了...！\n");

                set("startroom", "/d/shaolin/jianyu", ob);
                ob->apply_condition("bonze_jail", 60);
        }
}
