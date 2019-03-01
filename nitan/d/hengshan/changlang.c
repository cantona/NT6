// Last Modified by Sir on May. 22 2001
//Room: changlang.c 長廊

inherit ROOM;
void do_chat();

void create()
{
        set("short","長廊");
        set("long",@LONG
通往恆山白雲庵的後殿的一條長廊。往北便是是恆山派掌門人的居
所。南邊是恆山派白雲庵。
LONG);
        set("no_clean_up", 0);
        set("exits",([ /* sizeof() == 1 */
                "south" : __DIR__"baiyunan", 
                "north" : __DIR__"byahoudian",
        ]));
        set("coor/x", 40);
        set("coor/y", 3220);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}