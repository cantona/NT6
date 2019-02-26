// Last Modified by Sir on May. 22 2001
//Room: cangjingge.c 藏經閣

inherit ROOM;
void create()
{
        set("short","藏經閣");
        set("long",@LONG
這裏便是恆山派的藏經閣了。四周都是密密麻麻，高及頂棚的書架。
窗口下有一張大桌子，桌上放了幾本佛經。幾位小師太正在那專心研讀。
LONG);
        set("objects", ([             
                __DIR__"obj/fojing1"+random(2) : 1,             
        ]));
        set("exits",([ /* sizeof() == 1 */
                "west"  : __DIR__"byaeast", 
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 60);
        set("coor/y", 3210);
        set("coor/z", 100);
        setup();
}
