// Room: /d/suzhou/shuiwa1.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "划船塢");
        set("long",@long
這裏名為“畫船樓”，俗稱“划船塢”，相傳西施在此玩龍舟。向
南有一條直通太湖的人工開鑿的小溪。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "eastup"    : __DIR__"shiyuan",
                "southeast" : __DIR__"caixiangjing",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}