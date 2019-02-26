// Room: /d/wuyi/xianyutan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "仙浴潭");
        set("long", @LONG
高聳的石壁，營造了一個幽雅深邃的意境。一塘清澈的池水閃着粼
粼的波光。夏日的炎熱早就溶進雪花泉的淙淙碧流水響中。當你步下天
遊峯的仙浴潭，疲倦的身心頓然有了真切的撫慰，煩惱與憂慮不覺淡化
成淺淺的寧靜心境。這，也許就是仙人與凡人的區別吧？超然物外的仙
人沒有凡人擺脱不了的遠慮近憂。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : __DIR__"tianyoufeng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1390);
        set("coor/y", -4960);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}
