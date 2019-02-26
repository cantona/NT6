// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "水龍軒");
        set("long", @LONG
這裏是桃花島主黃藥師日常起居活動的地方，軒內陳設十分簡單。四
壁掛着一些晉人字畫，中間一副墨跡淋漓的條幅(tiaofu)，正是黃藥師時
常吟頌的《水龍吟》。門楣上嵌着一個黑黝黝的鐵八卦(bagua)，桌上零
散放着幾隻茶杯，一部翻開的阮籍詩鈔，一張當書籤的字紙，除此之外再
無長物。西面和北面各有一道長廊。
LONG );
        set("cost", 2);
        set("item_desc", ([
                "tiaofu" : "放船千里凌波去，略為吳山留顧。雲屯水府，濤隨神女，九江東注。北客翩然，壯心偏\n"
                           "感，年華將暮。念伊蒿舊隱，巢由故友，南柯夢，遽如許。回首妖氛未掃，問人間何處？\n"
                           "奇謀復國，可憐無用，塵昏白扇。鐵鎖橫江，錦帆衝浪，孫郎良苦。但愁桂棹，悲吟樑\n"
                           "父，淚流如雨 。。\n",
                "bagua" : "這個鐵八卦卦象排得零零落落，歪歪斜斜，既非伏羲先天八卦，也非文王\n"
                          "後天八卦，不知道派什麼用場。\n",
        ]));
         
        set("exits", ([
                "west" : __DIR__"changlang2",
                "out" : __DIR__"jingshe",
                "north" : __DIR__"changlang",
        ]));
        set("objects", ([
                // __DIR__"obj/paper1" : 1,
        ]));
        
        set("coor/x", 8990);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}