// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "監獄");
        set("long", @LONG
這是約莫兩丈見方的一間大石屋，牆壁都是一塊塊粗糙的大石所砌，
地下也是大石塊鋪成，牆角落裏放着一隻糞桶，鼻中聞到的盡是臭氣和
黴氣。牢房外卻可聽見燕語呢喃，向燕語處望去，只見一對燕子漸飛漸
遠，從數十丈外高樓畔的窗下掠過。那紗窗緊緊地關着，窗檻上卻總是
供着一盆鮮花，春天是茉莉、玫瑰，夏天是丁香、鳳仙。從西面牆上的
小窗望去，可以見到翰林府的一角。
LONG );

        set("exits", ([
                "west" : __DIR__"ymzhengting",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        create_door("west", "鐵門", "east", DOOR_CLOSED);
        set("cost", 0);
        set("coor/x", -7100);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}