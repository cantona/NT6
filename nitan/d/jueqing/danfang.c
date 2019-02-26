#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "丹房");
        set("long", @LONG
行至這裏，頓感熾熱更盛，只見裏面是間丈許見方的石室。
石室中央擺有一個一人多高的火爐(huo lu)。兩名粗工正在搬
堆柴炭，這兩人上身赤膊，下身只穿一條牛頭短褲，全身大汗
淋漓。
LONG);
        set("exits", ([
               "south"   : __DIR__"shufang",
               "west"    : __DIR__"zhulin3",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}