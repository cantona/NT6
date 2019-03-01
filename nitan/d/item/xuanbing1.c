// ROOM xuanbing1.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;
void create()
{
        set("short", "玄兵古洞");
        set("long", @LONG
這裡是玄兵古洞，四面洞壁之上結滿了石英的柱狀結晶體，顯得十
分漂亮。前方一個巨大的爐子前站著一位長髯老者正看著爐火想著什麼
心事，旁邊幾個彪形大漢正揮舞著錘頭敲打著一塊似乎總也燒不紅的什
麼金屬。旁邊仔細的放著幾把剛剛出爐的兵器。那種駭人的殺氣竟是從
這些兵器上散發出來的。
LONG );
        set("exits", ([
                "out" : __DIR__"xuanbing",
        ]));
        set("objects" , ([
                //__DIR__"npc/ouyezi" : 1,
        ]) );
        set("coor/x", -41200);
        set("coor/y", 8980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
