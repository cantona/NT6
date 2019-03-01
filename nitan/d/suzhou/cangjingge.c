// Room: /d/suzhou/cangjingge.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "藏經閣");
        set("long",@long
中間排列著五排大書架。四周則陳列矮幾，以供閱讀。幾位老僧手
執經卷，正在閉目凝思。
long);
        set("exits",([
                "south" : __DIR__"dxbdian",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1119);
	set("coor/y", -1151);
	set("coor/z", 29);
	setup();
        replace_program(ROOM);
}