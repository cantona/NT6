// Room: /qingcheng/zoulang3.c
// Date: Aug. 10 1998 by Winder

inherit RESTROOM_OUT;
void create()
{
        set("short", "鬆風西廊");
        set("long", @LONG
這裡是鬆風觀中連貫操練場和西廂的走廊，鬆風觀高矗山頂，從走
廊望去，青山鳥寂，幽谷風生，漫天薄霧時時彌散在長林翠竹之間。自
古號稱：“青城天下幽”，不妨在此體味。這裡南邊是客房，北邊是廚
房，西邊常常關著門的是本派弟子的練功休息室。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "east"  : __DIR__"caochang",
                "north" : __DIR__"chufang",
                "south" : __DIR__"kefang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -840);
        set("coor/z", 90);
        set("door_name","大門");
        set("door_dir","west");
        set("restroom",__DIR__"xiuxishi");
        set("open_door_msg","門上掛了個牌子：休息中。\n");
        set("no_one_msg",   "門上掛了個牌子：青城弟子休息室。\n");
        set("inside_msg",   "門上掛了個牌子：打擾一次、罰跪三天！\n");
        set("item_desc/door",(: look_men : ));
        set("item_desc/men", (: look_men : ));
        setup();
}