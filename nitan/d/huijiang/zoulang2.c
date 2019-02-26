// Room: /d/huijiang/zoulang2.c
// Last Modified by winder on Sep. 12 2001

inherit RESTROOM_OUT;

void create()
{
        set("short", "走廊");
        set("long",@LONG
你走在一條長長的走廊上，四周沒有一個人，你的腳步聲傳得很遠，
兩旁池塘裏的殘荷上停了幾隻呱呱亂叫的青蛙，陣陣輕風吹來，令人慾
醉。南邊似乎有一扇門。
LONG );
        set("outdoors", "huijiang");        
        set("exits", ([
                "west"     : __DIR__"yixiangting",
                "northup"  : __DIR__"zongduo",
                "eastdown" : __DIR__"zoulang1" ,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50070);
        set("coor/y", 9140);
        set("coor/z", 10);
        set("door_name","門");
        set("door_dir","south");
        set("restroom",__DIR__"xiuxishi");
        set("open_door_msg","門上掛了個牌子：休息室。\n");
        set("no_one_msg",   "門上掛了個牌子：休息室。\n");
        set("inside_msg",   "門上掛了個牌子：打擾一次、罰跪三天！\n");
        set("item_desc/door",(: look_men : ));
        set("item_desc/men", (: look_men : ));
        setup();
}