// Room: /d/yanping/shandao1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "武夷山道");
        set("long", @LONG
你走在窄窄的武夷山小道上，山路崎嶇，密林森森，常有長蟲野獸
出沒。所謂“閩道更比蜀道難”，誠不相欺。西面隔著崇陽溪，就是奇
秀甲于東南的武夷山了。
LONG );
        set("exits", ([
                "northup" : __DIR__"erbapu",
                "southup" : __DIR__"yidao1",
                "west"    : "/d/wuyi/wuyigong",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jiangnan");
        set("coor/x", 1500);
        set("coor/y", -5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}