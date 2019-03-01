// Room: /lingzhou/malan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "馬欄");
        set("long", @LONG
這裡是驃騎營的馬欄，清一色的蒙古高頭戰馬。西夏軍中多是騎
兵，所以行軍作戰來去如風，快若閃電，西夏鐵騎的彪悍連大遼的騎
兵都頗有不如。驃騎營的戰馬俱是精選，膘肥體壯，馬夫們正給馬槽
裡添黑豆和草料，一股馬糞味和草料的混合味道飄了過來。
LONG );
        set("exits", ([
                "east" : __DIR__"biaoqiyin",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}