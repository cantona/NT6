// /yubifeng/yuanfeng.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "圓峰");
        set("long", @LONG
一路山脈從東北走向西南，另一路山脈自正南向北，兩路山脈相會
之處，便是這座形似圓墩的矮峰。峰覆積雪，映日生輝。
LONG );
        set("exits", ([
                "north"   : __DIR__"xiaolu3",
                "southup" : __DIR__"yuanfengding",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yubifeng");
        set("coor/x", 6100);
        set("coor/y", 5130);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}