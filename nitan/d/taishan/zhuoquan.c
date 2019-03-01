// Room: /d/taishan/zhuoquan.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "酌泉亭");
        set("long", @LONG
雲步橋東酌泉亭，又名觀瀑亭。北側有聯：“且依石欄觀飛瀑，再
渡雲橋訪爵鬆。”雲步橋周圍有“月色泉聲”、“雲步躋天”、“聳壑
昂霄”、“氣象巖巖”等題刻五十余處，真、草、隸、篆，諸體薈萃，
琳琅滿目。
LONG );
        set("exits", ([
                "west" : __DIR__"yunbu",
        ]));
        set("outdoors", "taishan");
        set("resource/water", 1);
        set("no_clean_up", 0);
        set("coor/x", 70);
	set("coor/y", 210);
	set("coor/z", 100);
	setup();
        replace_program(ROOM);
}