#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","冰洞");
        set("long",@LONG 
這是一個巨大的天然冰洞。做夢也沒想到，這溫泉水潭之下，
竟然有這樣一個天造地設的洞天福地。站在這裡，仿佛置身于水
晶寶庫一般，四周全是晶瑩剔透的冰塊，四面八方都是自己的倒
影，清可鑒發。
LONG);
        set("exits", ([
                    "up"  : __DIR__"water", 
                    "west" : __DIR__"wave2", 
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}