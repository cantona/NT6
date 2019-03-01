// pine_forest1.c 鬆林
// Last Modified by winder on Aug. 18 2002

inherit ROOM;


void create()
{
        set("short", "鬆林");
        set("long", @LONG
這是鬆林深處，暗無天日，朦朧中只感覺到左右前後到處都是樹影。
地上有一兩個死人骷髏，發著綠熒熒的磷光。你驚駭之間，一腳踩在鋼
針般的鬆針上！
LONG
        );
        
        if (random(2)) 
                set("objects", ([ __DIR__"obj/pine" : 1]));
        else                                         
                set("objects", ([ __DIR__"obj/songguo" : 1]));

        
        set("exits", ([
                "north" : __DIR__"pine_road2",
                "south" : __DIR__"pine_forest"+(2+random(4)),
        ]));
        set("outdoors", "wudang");
        setup();
}


void init()
{
        object me = this_player();
        
        if( !objectp(query_temp("armor/boots", me)) )
                me->receive_damage("qi", 10, "被鬆針紮死了");  

}
