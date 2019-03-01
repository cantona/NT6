// Room: /d/xiakedao/xkroad6.c
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
        set("short", "漁村小屋");
        set("long", @LONG
小村的漁民小屋十分簡陋，幾乎沒什麼家當，壁上掛滿了早用舊
了的漁具。大概大人都出海了，只有一個小孩在屋裡，看到你進來一
臉驚惶。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "south"   : __DIR__"xkroad5",
        ]));
        set("objects", ([
                __DIR__"npc/kid": 1,
                "/kungfu/class/xiakedao/zhangsan2" : 1,
        ]));
        set("coor/x", -1390);
        set("coor/y", -8990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
