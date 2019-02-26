// Room: /d/quanzhou/qingyuandong.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "清源洞");
        set("long", @LONG
從虎乳泉往上，就看到一個山門，門上刻着「第一洞天」四個字。
門後有一觀空樓，樓宇盡處便是一洞曰「蜕巖」，即清源洞。相傳南宋
紹興有一道人裴姓者追趕一條傷害生靈的大蛇到了這裏，那蛇妖鑽入石
洞中，裴道人索性就在洞口上坐化了，因而又名「裴仙洞」。據聞此洞
深不可測，可通至洛陽江。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"huruquan",
                "northdown" : __DIR__"shanlu1",
                "westup"    : __DIR__"nantaiyan",
        ]));
	set("coor/x", -910);
	set("coor/y", -7520);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}