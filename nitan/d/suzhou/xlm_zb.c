#include <ansi.h>

inherit ROOM;

#define PLACE "sz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修羅門總壇");
        set("long", @LONG
這裏是修羅門的總部，整個房間都陰森森的，正中是一個大火盆，
正噴發着幽藍的火焰。讓人覺得不顫而慄。前台擺放着一張鏤金象牙
牀，倒吊的竹簾，映出一個模糊的輪廓。想必就是那神祕莫測的玉羅
剎了。一側的牆上掛着任務牌（paizi）。
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
