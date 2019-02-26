// Room: /d/taishan/dongling.c
// Last Modified by Winder on Aug. 25 2001

inherit RESTROOM_OUT;

void create()
{
        set("short", "東靈殿");
        set("long", @LONG
這裏是泰山派的根本重地。殿內佈置肅穆，正中神案上泰山派開派
祖師東靈道長的牌位和畫像。神案上香爐裏插着三柱清香，香煙裊裊上
升，散發着一股檀香味。
    後殿現在是泰山派弟子練功的休息間。
LONG );
        set("exits", ([
                "east"    : __DIR__"riguanroad2",
                "westup"  : __DIR__"riguanroad1",
        ]));
        set("no_clean_up", 0);
        set("door_name","殿門");
        set("door_dir","north");
        set("restroom",__DIR__"dongling1");
        set("open_door_msg","門上掛了個牌子：休息室。\n");
        set("inside_msg",   "門上掛了個牌子：打擾一次、罰跪三天！\n");
        set("no_one_msg",   "門上掛了個牌子：休息室。\n");
        set("item_desc/door",(: look_men : ));
        set("item_desc/men", (: look_men : ));
        set("coor/x", 60);
	set("coor/y", 300);
	set("coor/z", 190);
	setup();
}