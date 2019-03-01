// Room: /d/suzhou/xingchunqiao.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "行春橋");
        set("long",@long
順著石湖岸邊走就來到了行春橋，你站在行春橋的石級上，極目遠
望，湖水接天，群山蜿蜒，塔影倒影，美若畫卷。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "east" : __DIR__"shihu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1090);
	set("coor/y", -1120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}