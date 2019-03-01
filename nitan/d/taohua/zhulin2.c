// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "綠竹林");
        set("long", @LONG
竹林全是由綠色方竹構成，林內有座竹枝搭成的涼亭，亭上橫額寫着
“積翠亭”三字。亭中竹几竹椅全是多年之物，用得潤了，現出淡淡黃光。
竹亭之側並肩生着兩棵大樹，枝幹虯盤，只怕已是數百年的古樹。蒼樺翠
竹，清幽無比。
LONG );
        set("exits", ([
                "east"  : __DIR__"zhulin3",
                "south" : __DIR__"zhulin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}