// Room: /heizhao/dongxiang.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "東廂房");
        set("long", @LONG
這裏是一燈大師的弟子們休息的地方。靠東窗户下安放着一排
矮榻上，整整齊齊擺疊着四套鋪蓋，窗台上一塵不染。窗外羣山點
點，霧海生滅，流雲往返。在此一宿，俗念頓消。門邊的洗漱用具
也收拾得很乾淨，青磚地面想來也是天天打掃，絕無點塵。
LONG );
        set("no_clean_up", 0);
        set("sleep_room", "1");
        set("no_fight", "1");
        set("exits", ([
                "west"       : __DIR__"chanyuan",
        ]));
        set("coor/x", -5010);
        set("coor/y", -1200);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}