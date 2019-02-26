// Room: /lingzhou/daodian.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "刀店");
        set("long", @LONG
這是一家以賣西域特產“英吉兒”小刀出名的兵器鋪，上百把各
式各樣的“英吉兒”小刀整整齊齊的擺放在櫃枱上，説是小刀卻尺寸
型制大不相同，既有長僅一寸的柳葉飛刀、也有長達三尺的阿拉伯彎
刀。最多的還是長六寸，寬三分，背厚一黍，刃薄如紙的匕首櫃枱後
面的牆上也掛着些長劍，鋼刀，鐵杖等中原兵器。
LONG );
        set("exits", ([
                "north"  : __DIR__"xidajie",
        ]));
        set("objects", ([
                __DIR__"npc/daodianhuoji" :1,
        ]));
        set("coor/x", -6285);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}