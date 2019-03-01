// shulin0.c 樹林
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "小樹林");
        set("long", @LONG
走在小樹林當中，你只聞錚錚琴聲，一股淡淡白煙，帶著極甜的花
香，自密林深處傳出。一群乳白色的蜜蜂在你身旁飛來飛去。只見一塊
石碑(shibei)立在當眼ㄦ處。往東是一塊空地。其它方向盡是茂密的樹
林。
LONG        );
        set("outdoors", "gumu");
        set("item_desc", ([
                "shibei" : 
"

                        終南古墓，
                        外人止步。

",
        ]));
        set("exits", ([
                "west"    : __DIR__"shulin5",
                "east"    : __DIR__"shulin6",
                "north"   : __DIR__"shulin4",
                "southup" : __DIR__"shulin1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3200);
        set("coor/y", 80);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}