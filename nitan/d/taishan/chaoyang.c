// Room: /d/taishan/chaoyang.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "朝陽洞");
        set("long", @LONG
這裡是一個天然石穴，稍加整修，便深廣如屋，南辟向陽，舊名迎
陽、雲陽。洞後壁線刻元君像。洞南原有乾隆駐蹕亭，北有元君殿。洞
東南翠峰崛起，虯鬆附石，望之如老將軍披巾坐鞍馬，故名老人寨。下
有朗然子洞，系元初道士劉朗然修真處。洞東北為絕壁，名御風巖。
LONG );
        set("exits", ([
                "southeast" : __DIR__"wudafu",
                "northup"   : __DIR__"duisong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "taishan");
        set("coor/x", 30);
	set("coor/y", 220);
	set("coor/z", 120);
	setup();
        replace_program(ROOM);
}