//Edited by fandog, 01/31/2000
#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", HIR"赤壁"NOR);
        set ("long", @LONG
這是伸展在大江之中的一座小石山。臨江的峭壁上刻有“赤壁”兩
個大字，相傳是三國時期周瑜所書。三國時孫權與劉備合兵，在這裏用
火攻大破曹操的八十萬大軍，把曹軍的水兵、軍船一燃而盡。當時江面
烈火熊熊，把大江南岸的石壁照得通紅，從此，人們就將江邊這座小石
山為“赤壁”。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([ 
                "south" : __DIR__"huanghelou",
                "north" : __DIR__"matou2",
        ]));
  
        set("objects", ([
                "/d/beijing/npc/shiren" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -2210);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}