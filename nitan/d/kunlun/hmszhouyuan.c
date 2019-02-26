// Room: /d/kunlun/houyuan.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG"後院"NOR);
        set("long", @LONG
這裏是山莊的後院。此莊號稱“紅梅”，當有應有其根源。院子裏
就長着許多梅樹。每逢春天梅花盛開之時，到處一片火紅，分外美麗，
梅花飄香更是令人心曠神怡。北邊是“靈獒宮”。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"linggong",
                "west"  : __DIR__"hmszdating",
        ]));
        set("objects", ([ /* sizeof() == 2 */
                __DIR__"npc/guanjia" : 1,
        ]));
        set("outdoors", "hongmei");
        set("coor/x", -90020);
        set("coor/y", 10020);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}