// shulin5.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小樹林");
        set("long", @LONG
走在林中，你只聞錚錚琴聲，一股淡淡白煙，帶著極甜的花香，自
密林深處傳出。一群乳白色的蜜蜂在你身旁飛來飛去。不論往哪ㄦ走盡
是茂密的樹林。
LONG        );
        set("outdoors", "gumu");
        set("exits", ([
                "east"  : __DIR__"shulin0",
                "west"  : __FILE__,
                "south" : __DIR__"shulin4",
                "north" : __FILE__,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3210);
        set("coor/y", 80);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}