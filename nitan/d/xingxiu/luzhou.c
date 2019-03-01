// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "沙漠綠洲");
        set("long", @LONG
在沙漠的盡頭出現了一個綠洲。灌木叢中有一眼坎兒井。井台上有一個木杯
專供口渴的行人喝水。井邊是一塊瓜地。
LONG );
        set("resource/water", 1);

        set("exits", ([
                //"northeast" : __DIR__"shanjiao",
                "northeast" : __DIR__"tugu",
                "southeast" : __DIR__"nanjiang3",
                "south" : "/d/item/xuanbing",
        ]));

        set("objects", ([
                __DIR__"obj/donkey" : 1,
                __DIR__"obj/hamigua" : 2,
        ]));

        set("outdoors", "xiyu");
        set("no_map", "這裡的地形令人迷惑，無法繪制地圖。\n");

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

        if (arg != "water")
                return notify_fail("你要喝什麼?\n");

        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water)
        {
                set("water", current_water+30, me);
                message("vision", me->name()+"趴在坎兒井的井台上用木杯舀了一杯水喝。\n",
                        environment(me), ({me}) );
                write("你喝了一口井中從天山上流淌下來的雪水，簡直比蜜還甜。\n");
        } else
                write("逮著不要錢的水就這麼喝，至于嗎？\n");

        return 1;
}
