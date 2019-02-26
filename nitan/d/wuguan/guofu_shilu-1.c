inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
你走在一條石板路上，從這裏往東是物品房，你見有不少
人手裏拿着各樣的工具，從那邊過來，西面是郭府的大廳。
LONG);
        set("no_fight", 1);
        set("exits", ([
              "east" : __DIR__"guofu_wupinfang",
              "west" : __DIR__"guofu_dating",
              "north" : __DIR__"guofu_xuetang",
              "south" : __DIR__"guofu_zhangfang",
        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}
