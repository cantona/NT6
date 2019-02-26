// Room: /d/huijiang/buluo2.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "回部部落");
        set("long", @LONG
此處三面是樹林，北面的斜坡通向大草原，成羣的牛羊在草原上吃
草嘻戲。遠處天山山脈如同天地之間的一塊屏障，把後面的一切都遮擋
住了。四外是幾個帳篷。
LONG
        );
        set("outdoors", "huijiang");
        set("exits", ([ /* sizeof() == 4 */
                "west"      : __DIR__"zhangpeng3",
                "east"      : __DIR__"zhangpeng2",
                "south"     : __DIR__"buluo1",
                "northdown" : __DIR__"xiepo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50050);
        set("coor/y", 9060);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}