// Room: /d/taiwan/jilonggang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "雞籠港");
        set("long", @LONG
雞籠港，自海上遙望，狀似雞籠，而雞籠港口外的雞籠嶼亦貌如雞
籠，故漢族移民以雞籠名之。雞籠港位於台灣東北部，在台灣海峽的北
口，一面聚連東海和太平洋，以港埠聞名；港灣之東、南、西三面環山，
獨有北側為出海之口；市內有蚵殼港（西南邊）、田寮港（東邊）骸牛
稠港（西北邊）等三條短而淺的小溪，流入港灣。 
LONG );
        set("exits", ([
                "west" : __DIR__"danshui",
        ]));
        set("objects", ([
                __DIR__"npc/wokou": 3,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2550);
        set("coor/y", -6970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
