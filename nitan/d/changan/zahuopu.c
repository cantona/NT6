//Room: zahuopu.c

inherit ROOM;

void create()
{
        set("short", "雜貨鋪");
        set("long", @LONG
一間老字號的雜貨鋪。祖孫三代經營下來，在長安城南一帶已經
有了一些小名氣。這裏無論是油鹽醬醋，還是大米白麪，老百姓日常
生活需要的東西一樣都不少。再加上這裏的老掌櫃待客如賓，雜貨鋪
的生意看來一天比一天好。
LONG );
        set("exits", ([
                "south" : "/d/changan/huarui5",
        ]));
        set("objects", ([
                "/d/changan/npc/liu": 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10700);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}