inherit ROOM;

void create()
{
        set("short", "客廳");
        set("long", @LONG
這是一間寬敞的大廳，地上用大理石舖就的地面被打磨的像
鏡子一樣光滑，正中的三級台階上擺放著一長紅木大太師椅，椅
子的綢面上繡著狼蟲虎豹，非常威嚴。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"fyuan",
]));

        set("objects", ([
//        __DIR__"npc/guanjia" : 1,

]));

        setup();
        replace_program(ROOM);
}
