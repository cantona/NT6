// Room: /d/xiangyang/yaopu.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "藥鋪");
        set("long", @LONG
藥鋪不大，卻異常的整潔；正面是櫃枱，櫃枱後面是個大櫃子幾
百個小抽屜上一一用紅紙標着藥材的名稱；靠近屋頂的牆上懸着一塊
黑底金字的匾額，寫着『妙手回春』。地下幾個夥計正在分揀剛剛收
購來的草藥。東邊一張小韓桌兒，上面放着筆墨紙硯，桌後坐着一位
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