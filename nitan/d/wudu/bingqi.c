inherit ROOM;

void create()
{
        set("short", "兵器房");
        set("long", @LONG
這裏是五毒教存放武器的地方，四面靠牆全是兵器架，上面插滿
了各種兵器。  
LONG);

        set("exits", ([
                "west" : __DIR__"beiyuan",
        ]));
        set("objects", ([
                  __DIR__"obj/ganggou": 2,
                  __DIR__"obj/woodjian": 2,
        ]));
    
        setup();
        replace_program(ROOM);
}
