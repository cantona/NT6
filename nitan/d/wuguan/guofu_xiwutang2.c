#include <room.h>

inherit ROOM;

void create()
{
        set("short", "習武堂");
        set("long", @LONG
這裏是郭府的習武堂，堂內一個教頭在教着武功，幾個新
手正在向教頭學習功夫，堂子正上方掛着個匾，上面寫着吃得
苦中苦，放為人上人。
LONG);
        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"guofu_shilu-2",
        ]));
        setup();
        replace_program(ROOM);
}