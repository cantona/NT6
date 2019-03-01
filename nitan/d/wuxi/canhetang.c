// Room: /d/wuxi/canhetang.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "參和堂");
        set("long", @LONG
參和堂是無錫城的老字號藥舖了，濃濃的藥味早已經深入店堂裡的
每根椽柱之中，櫃台後的幾百個小抽屜上貼著各種中藥的名稱。藥舖帳
房坐在茶幾旁，獨自喝著茶，翻看著手上的帳單。一名小伙計站在櫃台
後招呼著顧客。櫃台上貼著一張發黃的廣告(guanggao)。
LONG );
        set("item_desc", ([
                "guanggao" : "本店出售以下藥品：
金創藥：\t五十兩白銀
無常丹由桃花島黃藥師所配，生死肉骨．
朱睛冰蟾救治百毒，無效包換．
其他神藥與老板面議。\n",
        ]));
        set("exits", ([
                "east" : __DIR__"northroad2",
        ]));
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
        set("coor/x", 1030);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}