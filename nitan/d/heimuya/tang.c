inherit ROOM;                           
      
void create()
{
        set("short", "令牌堂");
        set("long", @LONG
這裏是黑木崖的第三大堂青龍堂的令牌室。室內青磚鋪地。桌上
有一盒子(box1)。
LONG );
        set("exits", ([        
            "west"      : __DIR__"qing",
        ]));
        set("item_desc", ([
            "box1": "這是個放令牌的盒子，不過以被人打開，空空如也 。\n",
               ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}