// Last Modified by Sir on May. 22 2001
//Room: byahoudian.c 白雲庵後殿

inherit ROOM;
void do_chat();

void create()
{
        set("short","白雲庵後殿");
        set("long",@LONG
恆山白雲庵的後殿。是恆山派掌門人的居所。這裡供有一尊普賢菩
薩像。兩旁靠牆放著幾張太師椅，地上放著幾個蒲團。
LONG);
        set("no_clean_up", 0);
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"changlang",             
        ]));
        set("coor/x", 40);
        set("coor/y", 3230);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}