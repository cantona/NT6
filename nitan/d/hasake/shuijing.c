// shuijing.c
inherit ROOM;

void create()
{
        set("short", "坎兒井");
        set("long", @LONG
山丘下灌木叢中有一眼坎兒井，是牧民們的水源。井台上有一個木杯
專供口渴的行人喝水。井邊有一個由人踏動的水車，水渠從這裏一直連到
了東邊的馬廄。
LONG);
        set("resource/water", 1);
        set("exits", ([
                "eastup" : __DIR__"caochang",
                "southwest" : __DIR__"room-su",
                "northeast" : __DIR__"pmchang",                
        ]));
         set("objects", ([
                    __DIR__"obj/hamigua" : 2
        ]));
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}
int do_drink(string arg)
{
        int current_water;
        int max_water;
        object me;
        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water) {
            set("water", current_water+30, me);
            message("vision", me->name()+"趴在坎兒井的井台上用木杯舀了一杯水喝。\n"
            , environment(me), ({me}) );
            write("你喝了一口井中從天山上流淌下來的雪水，簡直比蜜還甜。\n");
        }
        else write("你再也喝不下了。\n");
        return 1;
}