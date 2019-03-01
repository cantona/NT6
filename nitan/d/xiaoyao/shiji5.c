// shiji5.c
// Modified by Winder June.25 2000

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "石級");
        set("long", @LONG
又行二百餘級，水聲已然振耳欲聾，前面並有光亮透入。走到石級
的盡頭，前面是個僅可容身的洞穴，探頭向外一眼望出去，外邊怒濤洶
湧，水流湍急，竟是一條大江。江岸山石壁立，嶙峋巍峨，看這情勢，
已是到了瀾滄江畔。
LONG );
        set("exits", ([
                "westdown" : __DIR__"shiji4",
                "out"      : "/d/wanjiegu/riverside1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", -21010);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}