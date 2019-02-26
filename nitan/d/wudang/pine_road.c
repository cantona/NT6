// pine_road.c 松林大道
// Last Modified by winder on Aug. 18 2002

inherit ROOM;

void create()
{
        set("short", "松林大道");
        set("long", @LONG
你走在山腳松林中的一條道路上，不時有道士打扮的人扛着紅松樹
木從身旁經過。西面是上山的路，兩邊是茂密的松樹林，林中伐木鏗鏘，
間或有大樹倒塌聲，「喀哧」作響。
LONG
        );
        set("outdoors", "wudang");

        set("exits", ([
                "eastdown" : __DIR__"jiejianyan",
                "west"     : __DIR__"xuanyuegate",
                "north"    : __DIR__"pine_road1",
                "south"    : __DIR__"pine_road2",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
