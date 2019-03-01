// Room: /d/songshan/junjigate.c
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "峻極山門");
        set("long", @LONG
嵩山絕頂，古稱“峻極”。極頂有一峻極禪院，本是佛教大寺，但
百年來卻已成為嵩山派掌門人的住所。這裡是峻極禪院山門，西上山路
可以到達封禪台。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shandao6",
                "northup"   : __DIR__"qianting",
                "westup"    : __DIR__"shandao7",
        ]));
        set("outdoors", "songshan");
        set("no_clean_up", 0);
        set("coor/x", -20);
        set("coor/y", 850);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}