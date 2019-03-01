inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
這是一片無邊無際的草原，半人高的青草隨風而動，正如
江湖中的你，隨著江湖之中洶湧的波濤，四處飄搖。你想到江
湖中的無奈，不禁滄然淚下。 
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "west" : __DIR__"caoyuan3",
                  "north" : __DIR__"caoyuan1",
        ]));

        setup();
        replace_program(ROOM);
}