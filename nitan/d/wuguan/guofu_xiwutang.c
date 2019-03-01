#include <room.h>

inherit ROOM;

void create()
{
        set("short", "習武堂");
        set("long", @LONG
這裡是郭府內的習武堂，堂內一個教頭在教著武功，幾個
新手正在向教頭學習功夫，堂子正上方掛著個匾，上面寫著吃
得苦中苦，放為人上人。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"guofu_shilu-2",
        ]));
        setup();
        replace_program(ROOM);
}