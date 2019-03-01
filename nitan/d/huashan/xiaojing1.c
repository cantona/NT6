// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "後山小徑");
        set("long", @LONG
這是華山後山的一條小徑，人跡鮮至。兩旁野草生得密密麻麻，
要不是有人帶領，誰也想不到這裡竟然有條小徑。
LONG );

        set("outdoors", "huashan");

        set("exits", ([ /* sizeof() == 1 */
                  "north":__DIR__"taogu",
        ]));

        setup();
        replace_program(ROOM);
}
 