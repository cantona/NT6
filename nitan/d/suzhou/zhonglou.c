// Room: /d/suzhou/zhonglou.c
// Last Modified by winder on May. 15 2001
inherit ROOM;
void create()
{
        set("short", "鐘樓");
        set("long", @LONG
這是一座磚木結構的寶塔，塔高七層，塔身作八角形，飛檐翹翎，
檐角上掛滿了一串串小銅鈴，隨風叮叮作響。塔身牆上鏤空雕繪著無數
佛陀們的坐像。一個個形態維肖，看來出自名匠之手。塔底入口處開了
一扇拱形的小木門，門扇兩側用彩漆塗繪，畫的是釋祖在靈山對諸天眾
佛講經時的情形。
LONG
        );
        set("outdoors","suzhou");
        set("exits", ([
                "east" : __DIR__"lingyansi",
//                "enter" : __DIR__"zhonglou1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1160);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}