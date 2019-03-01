// Room: /yangzhou/guanyindian.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "觀音殿");
        set("long", @LONG
觀音殿俗稱小南海，面西三楹。殿內供奉六尊白玉雕像，為明代雕
刻瑤台女神。殿外庭院，兩株百年古柏參天而立。殿前六角吹花門，通
“寒竹風鬆”半亭。出殿南方門“香海慈雲”，沿石級而下，可達“湖
上草堂”。
LONG );
        set("exits", ([
                "west"      : __DIR__"banting",
                "southdown" : __DIR__"caotang",
                "eastup"    : __DIR__"pingtai1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}