// baimatang.c
// Java Oct.10 1998

#include <ansi.h>
inherit ROOM;

int do_move(string arg);

void create()
{
        set("short", "白馬潭");
        set("long", @LONG
這個潭位於終南山主峯一帶，一條名叫庫峪河的上游。潭邊有一塊
比三間房子還要大的白石頭，這石頭中間低兩頭高，石頭的前半截伸在
水裏，後半截留在岸上。由伸在水中的那半截石頭下面還不時冒出一串
串白沫，老遠看去活似一匹騰空欲飛的烈馬，因此當地人都叫此潭為白
馬潭。往北是一條崎嶇的山路。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "northup" : __DIR__"shanlu6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3190);
        set("coor/y", 100);
        set("coor/z", 130);
        setup();
        replace_program(ROOM);
}