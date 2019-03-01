// Room: /d/songshan/eastpath2.c
// Last Modified by Winder on Jul. 15 2001

inherit RESTROOM_OUT;
void create()
{
        set("short", "東廊");
        set("long", @LONG
這裡是環繞池塘的走廊，畫闌雕棟，卻也美侖美奐。一路走來，腳
底木板響動，別有韻味。嵩岳獨立天心，八方天風，只吹得天邊雲起雲
落，滿山樹浪起伏。
LONG );
        set("outdoors", "songshan");
        set("exits", ([
                "south" : __DIR__"eastting",
                "north" : __DIR__"eastwuchang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 910);
        set("coor/z", 90);
        set("door_name","門");
        set("door_dir","east");
        set("restroom",__DIR__"xiuxishi");
        set("open_door_msg","門上掛了個牌子：休息室。\n");
        set("no_one_msg",   "門上掛了個牌子：休息室。\n");
        set("inside_msg",   "門上掛了個牌子：打擾一次、罰跪三天！\n");
        set("item_desc/door",(: look_men : ));
        set("item_desc/men", (: look_men : ));
        setup();
}