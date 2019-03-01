#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "青山");
        set("long", @LONG
山中樹木茂密，花開萬朵，傾耳細聽，可以聽見山溪流水的聲音，
風吹樹頁的聲音，如同一首大自然的樂曲，美妙動聽。
LONG );
        set("exits", ([
                  "northeast" : __DIR__"qingshan1",
                  "west" : __DIR__"road6",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("coor/x", -370);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
