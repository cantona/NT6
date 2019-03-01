// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "藥房");
        set("long", @LONG
這裡是黃藥師儲藏平日煉制藥材的地方，桃花島弟子也經常到這裡來
取用一些自己合用的藥物。散發出陣陣沁人心肺花香的就是桃花島名聞天
下的九花玉露丸，氣味刺鼻的則是解毒靈藥田七鯊膽散，顏色猩紅如血的
是療傷聖藥無常丹。北面是一道長廊。
LONG );
        set("exits", ([
                "north" : __DIR__"changlang2",
        ]));
        
        set("objects", ([
                __DIR__"npc/mianfeng" : 1,
        ]));
        
        set("coor/x", 8980);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ( (!myfam || myfam["family_name"] != "桃花島") && dir == "north" )
                return notify_fail("桃花島不留外客，你不能住在這裡！\n");

        if( query("gender", me) == "無性" && dir == "north" )
                return notify_fail("你不能住在這裡！\n");

        return ::valid_leave(me, dir);
}
*/