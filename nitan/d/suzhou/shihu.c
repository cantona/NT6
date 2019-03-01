// Room: /d/suzhou/shihu.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "石湖");
        set("long",@long
石湖是太湖的一個內陸支流，位于蘇州城南春秋時，越兵伐吳，橫
斷山麓，鑿石開湖，通故蘇，故名石湖。湖畔有座上方山，山頂矗立上
方塔。湖的北面橫跨高大的越城橋，湖東有當年越兵登陸的越來溪，湖
西隔著始建于南宋末年的行春橋。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "south" : __DIR__"tianpingshan",
                "west" : __DIR__"xingchunqiao",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1100);
	set("coor/y", -1120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}