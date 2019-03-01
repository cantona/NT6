// Room: /binghuo/shulin4.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "大樹林");
        set("long", @LONG
這裡已近島北，這島方圓極廣，延伸至北，不知盡頭，走出二十
余裡，只見一片濃密的叢林，老樹參天，陰森森的遮天蔽日。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "southwest" : __DIR__"yuanye1",
        ]));
        set("objects", ([
                __DIR__"npc/bear": 1,
        ]));
        setup();
        replace_program(ROOM);
}
