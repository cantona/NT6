#include <ansi.h>
inherit ROOM;

#define BISHOU  "/clone/lonely/xtbishou"
#define BAOJIA  "/clone/lonely/jsbaojia"

void create()
{
        object ob1, ob2;

        ob1 = find_object(BISHOU);
        if (! ob1) ob1 = load_object(BISHOU);

        ob2 = find_object(BAOJIA);
        if (! ob2) ob2 = load_object(BAOJIA);

        set("short","鰲府密室");
        set("long", @LONG
這裏是鰲拜府的密室，但是這裏似乎也沒有珍藏什麼特別
的寶貝。周圍黑漆漆的，頗為陰森恐怖。
LONG);
        set("exits", ([
                "up" :  __DIR__"aofu_shufang",
        ]));
        set("objects", ([
        ]));

        if (! environment(ob1))
               ob1->move(this_object());

        if (! environment(ob2))
               ob2->move(this_object());

        setup();
        replace_program(ROOM);
}

