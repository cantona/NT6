// Room: /u/zqb/tiezhang/hhyang-2.c
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", HIR "花圃" NOR);
        set("long", @LONG
只見這裡擺滿了茉莉、素馨、麝香籐、朱槿、玉桂、紅蕉，都是夏日盛
開的香花。院牆上又掛了枷木蘭、真臘龍誕等香珠，但覺馨意襲人，清芬滿
園。園中桌上放著幾盆新藕、甜瓜、枇杷、等鮮果，椅子上丟著把蒲扇，看
來是幫主休息的地方。
LONG        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"hhyuan-1",
]));
        set("no_clean_up", 0);
    set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}