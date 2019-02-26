// Room: /d/jiaxing/jiangpan1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "江畔");
        set("long", @LONG
一條大江橫亙在面前，江水浩浩，日日夜夜無窮無休地奔向大海。
這裏有一排烏柏樹，葉子似火燒般紅。兩棵大松樹下正圍着一堆村民，
聚精會神地聽着一個瘦削的老者説話。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "north":     __DIR__"njroad5",
                "southeast": __DIR__"jiangpan2",
        ]) );

	set("coor/x", 1270);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}