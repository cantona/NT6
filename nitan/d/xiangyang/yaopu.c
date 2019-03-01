// Room: /d/xiangyang/yaopu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "藥舖");
        set("long", @LONG
藥舖不大，卻異常的整潔；正面是櫃台，櫃台後面是個大櫃子幾
百個小抽屜上一一用紅紙標著藥材的名稱；靠近屋頂的牆上懸著一塊
黑底金字的匾額，寫著『妙手回春』。地下幾個伙計正在分揀剛剛收
購來的草藥。東邊一張小韓桌兒，上面放著筆墨紙硯，桌後坐著一位
老郎中。一股刺鼻藥味充滿了整個房間。
LONG );
        set("exits", ([
                "north" : __DIR__"eastjie1",
        ]));
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
        set("coor/x", -7810);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}