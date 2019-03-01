// Room: /d/kunlun/sleeproom.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short","臥室");
        set("long",@long
這裡是何太沖最寵愛的第五小妾五姑的臥房。剛一進房，撲鼻便是
一股藥氣，裡面還能聞到一股十分古怪的氣息，過了片刻，更覺得這氣
息忽濃忽淡，甚是奇特。床上躺著一個人，這人面向帳裡，喘氣甚急，
象是扯著風箱。窗子(window)都是緊緊關著。
long);
        set("item_desc", ([
                "window" : "房裡很悶，你不禁想打開窗子透透氣。\n",
        ]));
        set("objects",([
                __DIR__"npc/wugu" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"tieqinju",
        ]));
        create_door("west", "小門", "east", DOOR_CLOSED);
        set("coor/x", -119970);
        set("coor/y", 40140);
        set("coor/z", 90);
        setup();
}
