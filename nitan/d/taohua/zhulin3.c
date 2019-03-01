// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "綠竹林");
        set("long", @LONG
竹林全是由綠色方竹構成，林內有座竹枝搭成的涼亭，亭上橫額寫著
“積翠亭”三字。亭中竹幾竹椅全是多年之物，用得潤了，現出淡淡黃光。
竹亭之側並肩生著兩棵大樹，枝幹虯盤，只怕已是數百年的古樹。蒼樺翠
竹，清幽無比。
LONG );
         set("exits", ([
                "west"  : __DIR__"zhulin2",
                "north" : __DIR__"tingyu",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}