// Room: /binghuo/northboat2.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", "帆船");
        set("long", @LONG
這是一艘三桅海船，不知船主是誰。船上前後兩桅掛了白帆，準
備出海。船中艙中備有糧水，足夠支用半年。船上水手個個都是啞巴。
主桅上白帆飄動，獵獵作響。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
