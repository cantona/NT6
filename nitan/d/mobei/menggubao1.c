// Room: /d/mobei/menggubao1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "蒙古包");
        set("long", @LONG
蒙古人以遊牧為生，所居住的就是以毛氈所作的帳篷，通常稱為蒙
古包。帳篷中堆放了幾口箱籠，一邊是壺弓箭，蒙人自幼長於馬上，弓
箭是絕對少不得的。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"buluo1",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -200);
        set("coor/y", 5220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}