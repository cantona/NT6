//Cracked by Kafei
// yideng quest room 2

inherit ROOM;

int do_jump(string);
int do_lift(string);

void create()
{
        set("short", "瀑布下");
        set("long", @LONG
這裡是瀑布水底，水流急沖直下，你雙足使勁，以「千斤墜」的
功夫牢牢站穩，恰似中流砥柱，崎立不動。你發現金娃娃已經藏到一
塊巨石(stone)下面去了。
LONG );

        set("item_desc",([
        "stone" : "一塊巨大的巖石。\n",
        ]));
        set("invalid_startroom", 1);
        set("coor/x", -38000);
        set("coor/y", -80010);
        set("coor/z", -10);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
        add_action("do_lift", "lift");
}

int do_jump(string arg)
{
        object me = this_player();

        if ( !arg || arg != "bank" )
                return notify_fail( "什麼？\n");

        message_vision("$N縱身往岸上跳去。\n", me);
        me->move(__DIR__"yideng1");
        return 1;
}

int do_lift(string arg)
{   
        object me = this_player();

        if ( !arg || arg != "stone" )
                return notify_fail( "什麼？\n");

        message_vision("$N伸手向大石下抬去。\n", me);
        if ( me->query_str() < 26 ) {
                message_vision("$N伸手掀了幾掀，但大石紋風不動。\n", me);
                
        }
        else {
                message_vision("$N運足氣力推去，那巨石受水力與掌力夾擊，搖晃了幾下，擦過$N\n身旁，蓬蓬隆隆，滾落下面深淵中去了，響聲在山谷間激盪發出回音，\n轟轟然良久不絕。\n... ...\n\n", me);
                me->move(__DIR__"yideng3");
        }
        return 1;
} 

