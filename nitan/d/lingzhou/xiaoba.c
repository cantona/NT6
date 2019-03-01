// Room: /lingzhou/xiaoba.c
// Java Sep.23 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "小壩");
        set("long", @LONG
這裡是黃河邊的一條小支流大柳河與黃河匯合的地方，當地百
姓為了防止黃河的泥沙倒灌進大柳河而在這裡修了一座小小的石壩，
小壩不高，有三孔泄沙的洞，一扇結實的石閘門，兩邊是絞盤用來
控制閘門的升降。小壩使得大柳河兩岸的百姓免受了黃河泥沙的侵
擾。
LONG        );
        set("exits", ([
                "northeast" : __DIR__"huangyangtan",
                "southwest" : __DIR__"qingtongxia",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2895);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}