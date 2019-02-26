inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在登山的路徑上，路的左右各有一條大鐵鏈，象兩條長蛇向
山上山下蜿蜒爬去。滿眼是喬木夾道，如行於綠幕中。
LONG );
        set("exits", ([
                "northup" : __DIR__"haohanpo",
                "southup" : __DIR__"taizipo",
                "east" : __DIR__"mozhenjing",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -230);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}