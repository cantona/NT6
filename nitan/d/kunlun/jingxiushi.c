// Room: /d/kunlun/jingxiushi.c
// Last Modified by winder on Nov. 14 2000

inherit ROOM;

void create()
{
        set("short", "靜修室");
        set("long", @LONG
這裡是靜修室，地下順序地放著幾個蒲團，正中燒著幾柱香，輕煙
裊裊升起。幾位昆侖派弟子正盤膝坐在上面打坐靜修。
LONG );
        set("exits", ([
                "east"  : __DIR__"huayuan1",
        ]));
        set("objects", ([
                "/d/village/obj/zhujian" : 2,
        ]));
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -120000);
        set("coor/y", 40080);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}