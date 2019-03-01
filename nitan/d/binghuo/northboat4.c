// Room: /binghuo/northboat4.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;

inherit ROOM;

void create()
{
        set("short", "破帆船");
        set("long", @LONG
帆船在海流中無助地漂流著，沒有帆，也沒有槳。你無奈地看著
它越漂越北。船上水米皆盡，船體破碎支離，慘不忍睹，沒一塊完整
的地方了。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
