// Room: /d/taishan/yaocan.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "遙參亭");
        set("long", @LONG
這裏為岱廟前庭，舊稱草參門、草參亭。古人凡有事於泰山，必先
至此進行簡單參拜，而後入廟祭神。亭為二進院落。前院正殿，明清時
祀碧霞元君；兩側為東西配殿；院中有清康熙五十九年同知泰安州事張
奇逢立《禁止捨身碑》。
　　亭前石坊額書“遙參亭”。兩側鐵獅對峙，旗杆高豎。坊前為雙龍
池。池南為通天街，池西有唐槐一株，後院中立四角亭。
LONG );
        set("exits", ([
                "north" : __DIR__"daimiao",
                "south" : __DIR__"taishanjiao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 70);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}