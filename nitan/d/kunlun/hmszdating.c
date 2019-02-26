// Room: /d/kunlun/hmszdating.c
// Last Modified by winder on Jun. 29 2001

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"山莊大廳"NOR);
        set("long", @LONG
這裏是山莊會客之所，大廳之中坐着此間莊主。每逢年節，就有許
多僕在此等侯，希望主人能賞一些銀子。廳子兩旁放置着許多椅子和茶
機，是供客人座的。這裏雖然遠離中原，但來此之客卻是當真不少。廳
中壁上掛着一大副猛虎之圖。這裏有幾個童僕來回的侍侯着。
LONG        );
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"hmszhuang",
                "north" : __DIR__"hmsznuange",
                "east"  : __DIR__"hmszhouyuan",
        ]));
        set("objects",([
                __DIR__"npc/zhu"  :  1,
        ]));
        set("coor/x", -90030);
        set("coor/y", 10020);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}