// Room: /yangzhou/pingtai2.c
// Last Modified by Winder on Jul. 20 2000
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "平台");
        set("long", @LONG
館前平台圍以石欄，台中植有一對黑松，虯曲蒼勁。鬆間置一方石
壺，上刻“小蓬壺”，並有篆文聯：“借山疊石因成趣，種竹依花為有
香”。由綠柳堤西行逕達吹台。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "north" : __DIR__"lunlian",
                "west"  : __DIR__"chuitai",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", 130);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}