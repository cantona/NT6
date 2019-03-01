// pine_forest4.c 鬆林
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
        
        switch(random(13)){
        case 1:
                set("objects", ([ __DIR__"obj/songguo" : 2]));
                break;
        case 3:
                set("objects", ([ __DIR__"npc/snake" : 1]));
                break;
        case 5:
                set("objects", ([
                        __DIR__"obj/songguo" : 1,
                        __DIR__"npc/snake" : 1]));
                break;
        case 7:
                set("objects", ([ __DIR__"npc/snake" : 2]));
                break;
        case 9:
                set("objects", ([ __DIR__"obj/pine" : 1]));
                break;
        }                          
        
        set("exits", ([
                "south" : __DIR__"pine_forest"+(4+random(6)),
                "north" : __DIR__"pine_forest"+(3+random(7)),
                "west" : __DIR__"pine_forest"+(random(6)),
                "east" : __DIR__"pine_forest"+(random(4)),
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