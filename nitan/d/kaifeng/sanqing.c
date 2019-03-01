inherit ROOM;

void create()
{
        set("short", "三清殿");
        set("long", @LONG
三清殿供奉的是三清神像，不過開封府內的居民大多到大相國寺
去燒香還願了，這裡的香火並不旺。神像也蓬頭垢面無人理會。西行
去有座高高的閣樓，就是玉皇閣。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/sanqingxiang" : 1,
                  __DIR__"npc/xianghuo" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yanqing",
                  "west" : __DIR__"yuhuang",
        ]));

	set("coor/x", -5090);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}