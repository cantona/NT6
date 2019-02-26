inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是是戲院內演員的練功房，房內地上鋪着厚厚的地毯
有幾個演員摸樣的人在踢腿練功。西面的一塊大鏡子是幫他們
糾正動作的。你看着他們不禁也想動動身子骨，活動活動。
LONG);

        set("exits", ([
                "north" : __DIR__"xiyuan",
        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 1,
                __DIR__"npc/xizi2" : 1,
        ]));

        set("coor/x", -9050);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}