// Room: /d/suzhou/.c
// Last Modified by winder on Mar. 8 2001

#include <ansi.h>;
#include <room.h>;
inherit ROOM;

void create()
{
        set("short", "白雲泉");
        set("long",@long
一股清泉順着山麓而下，在這裏彙集成一潭泉水，當地人起了一個
名字叫“白雲泉”，這裏的泉水如線涓涓流入一石盂中，故又名“一線
泉”或“缽盂泉”。此泉大旱不竭，唐代茶聖陸羽評為“吳中第一泉”。
詩人白居易曾賦詩吟詠“天平山上白雲泉，雲本無心水自閒，何必奔衝
山下去，更添波浪向人間”。泉旁設有茶室，品茗名泉者絡繹不絕。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "westdown" : __DIR__"tianpingshan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1130);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}