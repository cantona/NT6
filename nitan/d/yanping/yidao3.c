// Room: /d/yanping/yidao3.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩浙驛道");
        set("long", @LONG
這裏是江邊驛道。南面就是延平府城了。東邊建溪中竹筏木排順流
而下，在礁石險灘中穿行，浪濤洶湧，激起層層水霧，彌散兩岸，與山
林蘆葦相交集，人稱“千古傳名黯淡灘，十船經過九船翻”，那裏便是
延平八景中的“黯淡洪濤”了。商人不知離別恨，槳櫓擊水、帆影搖風，
來往客商依舊匆匆。
LONG );
        set("exits", ([
                "northup"   : __DIR__"3800kan",
                "southeast" : __DIR__"fengguanyan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        setup();
        replace_program(ROOM);
}