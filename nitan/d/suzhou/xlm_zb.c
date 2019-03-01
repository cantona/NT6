#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修羅門總壇");
        set("long", @LONG
這裡是修羅門的總部，整個房間都陰森森的，正中是一個大火盆，
正噴發著幽藍的火燄。讓人覺得不顫而栗。前台擺放著一張鏤金象牙
床，倒吊的竹簾，映出一個模糊的輪廓。想必就是那神秘莫測的玉羅
剎了。一側的牆上掛著任務牌（paizi）。
LONG );

        set("objects", ([
                __DIR__"npc/boss-yu"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"hutong3",
        ]));

        setup();
}
#include <bang_bad.h>
