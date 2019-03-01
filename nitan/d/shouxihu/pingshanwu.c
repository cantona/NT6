// Room: /yangzhou/pingshanwu.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","平山堂塢");
        set("long",@LONG
這裡是平山堂塢。遊西湖者，從天寧寺側御碼頭下水，到此也得下
船了。當年乾隆，南巡也取此道。由此塢後山道拾階而上，共得九十九
級，便到蜀岡山中峰的大明寺了。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "northup" : __DIR__"pailou",
                "south"   : __DIR__"changdi3",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 120);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}